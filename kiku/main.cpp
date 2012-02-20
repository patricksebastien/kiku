/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca/kiku
 * 
 * 0.5
 * compile for newer version of debian based system
 * new languages: German & Portuguese
 * list arguments for process instead of process name only
 * patch wxwidgets to specify the number of characters before autocomplete
 * fix segfault (if liblo not enabled & kiku quit)
 * updated libpd
 * remove master_promts from english am
 * fix help (problem with encoding)
 * retouch of some windows gui to be compatible with gnome3
 * added beam option max
 * added basic application (kiku) & shortcut for japanese
 * 
 * do not load dict in memory? (german have 400k words to put in memory for autocomplete and writedictionary)...
 * 
 * 0.4
 * fix locale
 * add comment field in V2C Editor
 * alphabetical ordering in Active word
 * 
 * 0.3
 * fix taskbar message appears you don't support taskbar...
 * add mousemove
 * limit the refresh rate of audio meter
 * download Acoustic Model using cloud.github.com
 * added new word in English dictionary
 * 
 * 0.2
 * added alsa support
 * added liblo (open sound control)
 * added new xdotool command: activate & sleep & keyup & keydown & click
 * fix KP_* (need to be use with activate)
 * fix for threshold integer
 * 
 * 0.1
 * initial release
 * 
 * // WXWIDGETS
 * webupdate not always calling (wxthread with wxsocket problem)
 * 
 * // CLEAN
 * cleanup removeat and insertat
 * eventually clean the constructor of v2ceditor (this, this)
 * switch from dictionary file to grammar_manager julius API
 * the new build system for plugin fix the julius threading problem?
 * regex to look running process (maybe not needed anymore)
 * 
 * // IF REQUESTED
 * single word or grammar mode checkbox (http://julius.sourceforge.jp/en_index.php?q=en_grammar.html)
 * automatic unpause using volume threshold will be fix if no more julius threading problem (no meter when pause)
 * embed mkss, mkhmmbin...
 * tts
 * 
 * // NOTE
 * when updating this application #define VERSION "x" & update make_deb version and gui.fbp - engine
 * each time touch gui: 145 & 178 (pc_v2capplication / pc_v2cshortcut) = wxCB_SORT
 * wxjson (include) - if new: jsonval.cpp in wxJSONValue::Item() //wxLogTrace( traceMask, _T("(%s) actual object: %s"), __PRETTY_FUNCTION__, GetInfo().c_str()); (fix bug in 64bit)
 * when updating xdotool / libpd - copy *.h to kiku
 * 64 bit: cp 64 bit version of libpd.a & libxdo.a
 * 
 * // LANGUAGE
 * Portuguese
 * http://laps.ufpa.br/falabrasil/files/LapsAM-1.5-16k-SimonBR.rar
 * http://laps.ufpa.br/falabrasil/files/dicionario_stress.rar
 * http://www.laps.ufpa.br/falabrasil/simonbr.php
 * 
 * Sphinx (will need to convert)
 * http://sourceforge.net/projects/cmusphinx/files/Acoustic%20and%20Language%20Models/French%20Language%20Model/
 *********************************************************************/
#define DEBUGR
#include "main.h"

// gnome
#include <gconf/gconf-client.h>

// icons
#include "icon_ready.h"
#include "icon_update.h"
#include "icon_pause.h"
#include "icon_pretrig.h"
#include "icon_unknown.h"
#include "icon_think.h"
#include "icon_listening.h"
#include "icon_recognized.h"
#include "icon_need.h"

// initialize the application
IMPLEMENT_APP(MainApp);

// global
MainFrame *kiku;

wxArrayString noti; // notification
wxArrayString pretrigger;
wxArrayString trigger;
wxArrayString command;
wxArrayString comment;
wxArrayString type; // xdotool, shell
wxArrayString process; // processname
wxArrayString v2c; // shortcut, application, launcher
wxArrayString juliusformat_word; // dict of the language
wxArrayString juliusformat_pronoun; // dict of the language
wxString actionwaitingpretrigger;

pidrahash pidra;
pidcounthash pidcount;
wxArrayString processname; // fill if monitor process
wxArrayString processnamepid; // fill by monitor process
wxArrayString pspid; // fill by monitor process
wxArrayString pspnameid; // avoiding multiple call to v2cloading for the same processname
wxString finaldictprevious; // is there any change to the dictionary

bool juliusisready;
bool v2clauncher;
bool paused;
bool listening;
bool haveupdate;
bool freshinstall;
wxString updateurl;

////////////////////////////////////////////////////////////////////////////////
// libpd callback 
////////////////////////////////////////////////////////////////////////////////
void rfloat(const char *s, float myd) {
	wxString pdsend(s, wxConvUTF8);
	if(pdsend == "prvu") {
		wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, LIBPDPRVU_ID );
		event.SetInt((int)myd);
		wxGetApp().AddPendingEvent( event );
	}
}


////////////////////////////////////////////////////////////////////////////////
// application class implementation 
////////////////////////////////////////////////////////////////////////////////
bool MainApp::OnInit()
{
	// locale
	m_locale = new wxLocale;
	int sys_lang = wxLocale::GetSystemLanguage();
    if( sys_lang != wxLANGUAGE_DEFAULT )
    {
		m_locale->Init(sys_lang);         // set custom locale
		m_locale->AddCatalogLookupPathPrefix("locale");   // set "locale" prefix
		m_locale->AddCatalog("wxproton");            // our private domain
		m_locale->AddCatalog("wxstd");            // wx common domain is default
		// Restore "C" numeric locale
		setlocale(LC_NUMERIC, "C");
    }
	
	// web update / download language
	wxSocketBase::Initialize();
	
	kiku = new MainFrame( NULL );
	SetTopWindow(kiku);
	
	// TODO bundle (many sizes)
	wxMemoryInputStream istream(ready_png, sizeof(ready_png));
	wxBitmap *iconpng = new wxBitmap(wxImage(istream, wxBITMAP_TYPE_PNG));
	wxIcon icontb;
	icontb.CopyFromBitmap( *iconpng );	
	kiku->SetIcon(icontb);
	
	wxStandardPaths stdpath;
	
	wxString current_desktop;
	wxGetEnv("XDG_CURRENT_DESKTOP", &current_desktop);
	if(!wxFileExists(stdpath.GetUserDataDir()+"/language/julius.conf")) {
		kiku->Show();
	} else {
		// Add an exception for Unity (kiku doesn't support the new indicator system)
		if(current_desktop == "Unity") {
			kiku->Show();
		} else {
			kiku->Hide();
		}		
	}
	
	// callback function of julius
	Bind(wxEVT_COMMAND_TEXT_UPDATED, &MainFrame::onJuliusPronun, kiku, PRONUN_ID);
	Bind(wxEVT_COMMAND_TEXT_UPDATED, &MainFrame::onJuliusSentence, kiku, SENTENCE_ID);
	Bind(wxEVT_COMMAND_TEXT_UPDATED, &MainFrame::onJuliusScore, kiku, SCORE_ID);
	Bind(wxEVT_COMMAND_TEXT_UPDATED, &MainFrame::onJuliusReady, kiku, READY_ID);
	Bind(wxEVT_COMMAND_TEXT_UPDATED, &MainFrame::onJuliusWatch, kiku, WATCH_ID);
	//Bind(wxEVT_COMMAND_TEXT_UPDATED, &MainFrame::onJuliusLevelMeter, kiku, LEVELMETER_ID);
	
	// web thread
	Bind(wxEVT_COMMAND_TEXT_UPDATED, &MainFrame::OnWeb, kiku, WEB_ID);
	
	// libpd callback function
	Bind(wxEVT_COMMAND_TEXT_UPDATED, &MainFrame::libpd_prvu, kiku, LIBPDPRVU_ID);
	
	#if wxUSE_FS_INET && wxUSE_STREAMS && wxUSE_SOCKETS
		wxFileSystem::AddHandler(new wxInternetFSHandler);
	#endif

	return true;
}


////////////////////////////////////////////////////////////////////////////////
// main application frame implementation 
////////////////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(MainFrame,wxFrame)
    EVT_TIMER(PROCESSTIMER_ID, MainFrame::OnMonitorTimer) // monitor process name to match v2a
	EVT_TIMER(RESETICONTIMER_ID, MainFrame::OnResetIconTimer) // reset the original icon
	EVT_TIMER(UNPAUSETIMER_ID, MainFrame::OnUnpauseTimer) // reset the original icon
END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow *parent) : MainFrameBase( parent )
{		
	// libpd
	libpd_init();
	libpd_bind("prvu");
	libpd_floathook = (t_libpd_floathook) rfloat;
	
	// input channel, output channel, sr, one tick per buffer
	libpd_init_audio(1, 1, 16000, 4); // if users report glitch: check tick per buffer
	
	// compute audio    [; pd dsp 1(
	libpd_start_message(1);
	libpd_add_float(1.0f);
	libpd_finish_message("pd", "dsp");

	// open patch
	libpd_openfile("kiku.pd", "/usr/lib/kiku");
	
	// xdotool
	xdo = xdo_new(getenv("DISPLAY"));
	xdotoolwindow = 0;
	xdotooldelay = 12000;
	
	// standard path
	stdpath = wxStandardPaths::Get();

	// keyboard shortcut - CTRL+Q
	const int rid = wxNewId();
	Connect(rid,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainFrame::OnQuit);
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_CTRL, (int) 'q', rid);
    wxAcceleratorTable accel(1, entries);
    MainFrame::SetAcceleratorTable(accel);
	
	// icons
	wxImage::AddHandler(new wxPNGHandler);
	LoadPngIcon(ready_png, sizeof(ready_png), 0); // ready
	LoadPngIcon(update_png, sizeof(update_png), 1); // update available
	LoadPngIcon(pause_png, sizeof(pause_png), 2); // pause
	LoadPngIcon(pretrig_png, sizeof(pretrig_png), 3); // pre-trig
	LoadPngIcon(unknown_png, sizeof(unknown_png), 4); // unknown word
	LoadPngIcon(think_png, sizeof(think_png), 5); // thinking
	LoadPngIcon(listening_png, sizeof(listening_png), 6); // listening
	LoadPngIcon(recognized_png, sizeof(recognized_png), 7); // recognized word
	LoadPngIcon(need_png, sizeof(need_png), 8); // word need a pre-trig
	
	int tries = 0;
	// taskbar
	while ( !wxTaskBarIcon::IsAvailable() && tries < 20)
    {
		tries++;
		sleep(1);
    }
	if(tries == 20) {
		wxMessageBox
        (
            "There appears to be no system tray support in your current environment.",
            "Warning",
            wxOK | wxICON_EXCLAMATION
        );
	}
    m_taskBarIcon = new MainTaskBarIcon(this);
    icontb.CopyFromBitmap( *iconpng[0] );
	if (!m_taskBarIcon->SetIcon( icontb )) {
		wxMessageBox(wxT("Could not set icon."));
	}

	// global state
	juliusisready = false;
	paused = false;
	listening = true;
	// autopause
	nbmistake = 0;
	//aup_timer_started = false;
	//aup_timer_ispaused = true;
	aup_userpause = false;
	// web update
	webupdateicon = false;
	bm_update->Show(0);
	b_update->Show(0);
	
	// process timer
	m_timer = new wxTimer(this, PROCESSTIMER_ID);
	
	// reseticon timer
	reseticonm_timer = new wxTimer(this, RESETICONTIMER_ID);
	
	// unpause timer
	unpausem_timer = new wxTimer(this, UNPAUSETIMER_ID);

	// flags
	actionwaiting = false;
	unknown = false;
	recognized = false;
	needpretrig = false;

	// language gui
	st_languagedownloading->Hide();
	g_languagedownloading->Hide();
	
	// eye
	notify_init("kiku");
    osd = xosd_create(2);
    if (!osd) {
        wxMessageBox("Error creating XOSD notification, please report this bug: kiku@11h11.com");
    }
    xosd_set_timeout(osd, sp_notdelay->GetValue());
    xosd_set_colour (osd, "white");
    xosd_set_outline_colour(osd, "black");
	xosd_set_font(osd, "-adobe-helvetica-bold-r-normal-*-17-120-100-100-p-182-iso8859-1");
    xosd_set_outline_offset (osd, 3);
    xosd_set_align (osd, XOSD_right);
    xosd_set_vertical_offset(osd, 30);
	
	// check if julius.conf exist, if not it's a brand new installation
	if(!wxFileExists(GetCurrentWorkingDirectory()+"/language/julius.conf")) {
		// ~/.kiku
		if(!wxDirExists(stdpath.GetUserDataDir())) {
			if (!wxMkdir(stdpath.GetUserDataDir())) {
				wxMessageBox("Problem creating ~/.kiku!");
			}
			if (!wxMkdir(stdpath.GetUserDataDir()+"/v2c")) {
				wxMessageBox("Problem creating ~/.kiku/v2c!");
			}
		}
		
		// create preference.conf
		createpreference();
		
		// fetch preference.conf
		readpreference();
		
		// disable notebook
		p_recognition->Enable(0);
		p_V2C->Enable(0);
		p_configutation->Enable(0);
		p_engine->Enable(0);
		p_audio->Enable(0);
		
		// statusbar
		sb->SetStatusText("welcome to kiku!", 0);
		
		// go to notebook language
		m_nb->SetSelection(5);
		
		// to not free the thread onquit
		freshinstall = true;
		
	
	} else {
		// fetch preference.conf
		readpreference();
	
		// web update
		haveupdate = false; // for tb
		startwebthread("/KIKU/packages.txt");
		
		// to free the thread onquit
		freshinstall = false;
		
		// liblo
		if(cb_oscenable->GetValue()) {
			EnableOSC();
		}

		// load v2c
		V2cApplicationLoad(); // fill the V2C panel
		V2cShortcutLoad();  // fill the V2C panel
		v2cloading();
		
		// start julius thread (infinite loop)
		startjuliusthread();
	}
}


////////////////////////////////////////////////////////////////////////////////
// Gnome
////////////////////////////////////////////////////////////////////////////////
void MainFrame::gnome_cr(const gchar * command, const gchar * defaultApp)
{
    gchar * default_app;
    GConfClient *client;
    client = gconf_client_get_default ();
    if(command!=NULL)
    {
        default_app = gconf_client_get_string (client, command, NULL);
	if (default_app != NULL)
        {
            g_spawn_command_line_async(default_app, NULL);
        }
        else
	{
            g_spawn_command_line_async (defaultApp, NULL);
        }
    }
    else
    {
        g_spawn_command_line_async (defaultApp, NULL);
    }
}


////////////////////////////////////////////////////////////////////////////////
// Libpd
////////////////////////////////////////////////////////////////////////////////
void MainFrame::libpd_prvu(wxCommandEvent& event) {
	static int interval = 0;
	if(interval > 5) {
		g_englevel->SetValue(event.GetInt());
		st_db->SetLabel(wxString::Format("%idB", event.GetInt()));
		interval = 0;
	}
	interval++;
}

void MainFrame::Onc_driver(wxCommandEvent& event)
{
	writejuliusconf("driver");
	if(c_driver->GetStringSelection() == "Alsa") {
		s_volume->Enable(0);
		c_filter->Enable(0);
		s_lp->Enable(0);
		s_hp->Enable(0);
		g_englevel->Show(0);
		st_db->Show(0);
	} else {
		s_volume->Enable(1);
		c_filter->Enable(1);
		s_lp->Enable(1);
		s_hp->Enable(1);
		g_englevel->Show(1);
		st_db->Show(1);
	}
	if(m_Julius && juliusisready) {
		juliusgentlyexit();
		startjuliusthread();
	}
}

void MainFrame::Ons_volume(wxScrollEvent& event)
{
	st_volume->SetLabel(wxString::Format("%i%%", event.GetInt()));
	libpd_float("volume", event.GetInt());
	writepreference();
}

void MainFrame::Onc_filter(wxCommandEvent& event)
{
	if(event.GetString() == "None") {
		s_lp->Enable(0);
		s_hp->Enable(0);
		libpd_float("filter", 0);
	} else if(event.GetString() == "1-order") {
		s_lp->Enable(1);
		s_hp->Enable(1);
		libpd_float("filter", 1);
	} else if(event.GetString() == "2-order (butterworth)") {
		s_lp->Enable(1);
		s_hp->Enable(1);
		libpd_float("filter", 2);
	}
	writepreference();
}

void MainFrame::Ons_lp(wxScrollEvent& event)
{
	st_lp->SetLabel(wxString::Format("%i hertz", event.GetInt()));
	libpd_float("lp", event.GetInt());
	writepreference();
}

void MainFrame::Ons_hp(wxScrollEvent& event)
{
	st_hp->SetLabel(wxString::Format("%i hertz", event.GetInt()));
	libpd_float("hp", event.GetInt());
	writepreference();
}


////////////////////////////////////////////////////////////////////////////////
// Icons
////////////////////////////////////////////////////////////////////////////////
void MainFrame::LoadPngIcon(const unsigned char *embedded_png, int length, int icon_number)
{
        wxMemoryInputStream istream(embedded_png, length);
        iconpng[icon_number] = new wxBitmap(wxImage(istream, wxBITMAP_TYPE_PNG));
}

////////////////////////////////////////////////////////////////////////////////
// Notebooks
////////////////////////////////////////////////////////////////////////////////
void MainFrame::Onm_nb( wxNotebookEvent& event )
{
	unsigned int nb_current_page = m_nb->GetSelection();
	if(nb_current_page == 6) {
		// load help
		html_help->LoadPage("http://www.workinprogress.ca/KIKU/help/help.html");
	} else if(nb_current_page == 5) {
		if(!wxFileExists(GetCurrentWorkingDirectory()+"/language/julius.conf")) {
			// load html help language / installed
			html_language->LoadPage("http://www.workinprogress.ca/KIKU/help/language_install.html");
		} else {
			// load html help language / installed
			if(language == "en") {
				html_language->LoadPage("http://www.workinprogress.ca/KIKU/help/language_installed.html");
			} else if(language == "jp" || language == "jp60k") {
				html_language->LoadPage("http://www.workinprogress.ca/KIKU/help/language_installed_jp.html");
			}
		} 
	} else if(nb_current_page == 1) {
		// first install go to import directly
		if(b_languagedownload->GetLabel() == "Downloaded") {
			m_nbv2c->SetSelection(2);
		} else {
			html_v2capplication->LoadPage("http://www.workinprogress.ca/KIKU/help/v2capplication.html");
		}
	}
}

void MainFrame::Onm_nbv2c( wxNotebookEvent& event )
{
	unsigned int nb_current_page = m_nbv2c->GetSelection();
	if(nb_current_page == 0) {
		html_v2capplication->LoadPage("http://www.workinprogress.ca/KIKU/help/v2capplication.html");
	} else if(nb_current_page == 1) {
		html_v2cshortcut->LoadPage("http://www.workinprogress.ca/KIKU/help/v2cshortcut.html");
	} else if(nb_current_page == 2) {
		html_import->LoadPage("http://www.workinprogress.ca/KIKU/help/import.html");
	}
}
////////////////////////////////////////////////////////////////////////////////
// Active Word
////////////////////////////////////////////////////////////////////////////////
void MainFrame::Onb_activeword( wxCommandEvent& event )
{
	Dob_activeword();
}

void MainFrame::Dob_activeword()
{
	m_activeword = new ActiveWord(this);
	m_activeword->Show();
}

////////////////////////////////////////////////////////////////////////////////
// V2A
////////////////////////////////////////////////////////////////////////////////
void MainFrame::Onpb_v2capplication( wxCommandEvent& event )
{
		Dopb_v2capplication();
}

void MainFrame::Dopb_v2capplication()
{
	dv2capp = new V2cApplication(this, language);
	dv2capp->ShowModal();
}

void MainFrame::Onb_v2capplicationedit( wxCommandEvent& event )
{
	dv2capp = new V2cApplication(this, language, pc_v2capplication->GetStringSelection());
	dv2capp->ShowModal();
}

void MainFrame::Onpc_v2capplication( wxUpdateUIEvent& event )
{
	if(pc_v2capplication->GetCount()) {
		pb_v2capplicationedit->Enable(1);
		st_defined->Enable(1);
	} else {
		pb_v2capplicationedit->Enable(0);
		st_defined->Enable(0);
	}
}

void MainFrame::V2cApplicationReload()
{
	V2cApplicationLoad();
	pspnameid.Empty(); // allow monitor to reload the application
	v2cloading();
	if(m_Julius && juliusisready) {
		juliusgentlyexit();
		startjuliusthread();
	}
}

void MainFrame::V2cApplicationLoad()
{
	if(wxDirExists(GetCurrentWorkingDirectory()+"/v2c/")) {
		wxDir dir(GetCurrentWorkingDirectory()+"/v2c/");
		wxString filename;
		bool cont = dir.GetFirst(&filename, "*.v2a", wxDIR_FILES);
		pc_v2capplication->Clear();
		while ( cont )
		{
			pc_v2capplication->Append(filename.Mid(0, filename.Length() - 4));
			cont = dir.GetNext(&filename);
		}
		if(pc_v2capplication->GetCount()) {
			pc_v2capplication->SetSelection(0);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// V2S
////////////////////////////////////////////////////////////////////////////////
void MainFrame::Onpb_v2cshortcut( wxCommandEvent& event )
{
	Dopb_v2cshortcut();
}

void MainFrame::Dopb_v2cshortcut()
{
	dv2ceditor = new V2cEditor(this, language, "shortcut");
	dv2ceditor->ShowModal();
}

void MainFrame::Onpc_v2cshortcut( wxUpdateUIEvent& event )
{
	if(pc_v2cshortcut->GetCount()) {
		pb_v2cshortcutedit->Enable(1);
		st_shortcutdefined->Enable(1);
	} else {
		pb_v2cshortcutedit->Enable(0);
		st_shortcutdefined->Enable(0);
	}
}

void MainFrame::Onpb_v2cshortcutedit( wxCommandEvent& event )
{
	// show v2c editor
	dv2ceditor = new V2cEditor(this, language, "shortcut", pc_v2cshortcut->GetStringSelection());
	dv2ceditor->ShowModal();
}

void MainFrame::V2cShortcutReload()
{
	V2cShortcutLoad();
	pspnameid.Empty(); // allow monitor to reload the application
	v2cloading();
	if(m_Julius && juliusisready) {
		juliusgentlyexit();
		startjuliusthread();
	}
}

void MainFrame::V2cShortcutLoad()
{
	if(wxDirExists(GetCurrentWorkingDirectory()+"/v2c/")) {
		if(wxFile::Exists(GetCurrentWorkingDirectory()+"/v2c/shortcut.v2s")) {
			wxFileInputStream input(GetCurrentWorkingDirectory()+"/v2c/shortcut.v2s");
			wxJSONValue  root;
			wxJSONReader reader;
			int numErrors = reader.Parse( input, &root );
			if ( numErrors > 0 )  {
				// no more stuff in it delete it
				wxRemoveFile(GetCurrentWorkingDirectory()+"/v2c/shortcut.v2s");
				pc_v2cshortcut->Clear();
			} else {
				wxJSONValue modules = root["Actions"];
				pc_v2cshortcut->Clear();
				if (modules.IsArray() ) {
					for ( int i = 0; i < modules.Size(); i++ ) {
						pc_v2cshortcut->Append( modules[i]["Trigger"].AsString().Lower() );
					}
				}
				if(pc_v2cshortcut->GetCount()){
					pc_v2cshortcut->SetSelection(0);
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// IMPORT
////////////////////////////////////////////////////////////////////////////////
void MainFrame::Onb_v2cimportapp( wxCommandEvent& event )
{
	if(b_v2cimportapp->GetLabel() == "Download") {
		if(!listv2c("application")) {
			wxMessageBox("Problem downloading");
		} else {
			pc_v2cimportapp->SetSelection(0);
			b_v2cimportapp->SetLabel("Install");
		}
	} else if(b_v2cimportapp->GetLabel() == "Install") {
		if(!getv2c("application")) {
			wxMessageBox("Problem installing");
		}
	}
}

void MainFrame::Onpc_v2cimportapp( wxCommandEvent& event )
{
	importhtml("application");
}

void MainFrame::Onb_v2cimportshortcut( wxCommandEvent& event )
{
	if(b_v2cimportshortcut->GetLabel() == "Download") {
		if(!listv2c("shortcut")) {
			wxMessageBox("Problem downloading");
		} else {
			pc_v2cimportshortcut->SetSelection(0);
			b_v2cimportshortcut->SetLabel("Install");
		}
	} else if(b_v2cimportshortcut->GetLabel() == "Install") {
		if(!getv2c("shortcut")) {
			wxMessageBox("Problem installing");
		}
	}
}

void MainFrame::Onpc_v2cimportshortcut( wxCommandEvent& event )
{
	importhtml("shortcut");
}

void MainFrame::importhtml(wxString v2c)
{
	if(v2c == "application") {
		html_import->LoadPage(appurlhtml.Item(pc_v2cimportapp->GetSelection()));
	} else if(v2c == "shortcut") {
		html_import->LoadPage(shortcuturlhtml.Item(pc_v2cimportshortcut->GetSelection()));
	}
}
/*
 * TODO when export is implemented 
void MainFrame::Onb_v2cimportfp( wxCommandEvent& event )
{
	if(!gunzipv2c(pfp_v2cimport->GetPath())) {
		wxMessageBox("Problem installing");
	} else {
		importsuccess();
	}
}

// is this file .gz
void MainFrame::Onb_v2cimportpf( wxUpdateUIEvent& event )
{
	if(pfp_v2cimport->GetPath().Mid(pfp_v2cimport->GetPath().Length() - 3) == ".gz") {
		b_v2cimportpf->Enable(1);
	} else {
		b_v2cimportpf->Enable(0);
	}
}
*/
bool MainFrame::listv2c(wxString v2c)
{
	wxString urltxt;
	if(v2c == "application") {
		if(language == "en") {
			urltxt = "/KIKU/v2c/v2c_application.txt";
		} else if(language == "jp" || language =="jp60k") {
			urltxt = "/KIKU/v2c/v2c_application_ja.txt";
		} else if(language == "german") {
			urltxt = "/KIKU/v2c/v2c_application_german.txt";
		} else if(language == "portuguese") {
			urltxt = "/KIKU/v2c/v2c_application_portuguese.txt";
		}
	} else if(v2c == "shortcut") {
		if(language == "en") {
			urltxt = "/KIKU/v2c/v2c_shortcut.txt";
		} else if(language == "jp" || language =="jp60k") {
			urltxt = "/KIKU/v2c/v2c_shortcut_ja.txt";
		} else if(language == "german") {
			urltxt = "/KIKU/v2c/v2c_shortcut_german.txt";
		} else if(language == "portuguese") {
			urltxt = "/KIKU/v2c/v2c_shortcut_portuguese.txt";
		}
	}
	wxHTTP get;
	get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
	get.SetTimeout(10);
	int tried = 0;
	while (!get.Connect("www.workinprogress.ca")) {
		if(tried > 2) {
			return 0;
		}
		wxSleep(2);
		tried++;
	}
	wxInputStream *httpStream = get.GetInputStream(urltxt);
	if (get.GetError() == wxPROTO_NOERR)
	{
		const int DLBUFSIZE = 4096;
		unsigned char buffer[DLBUFSIZE+1];
		wxString m_dataRead;
		do {
			httpStream->Read(buffer, DLBUFSIZE);
			size_t bytes_read = httpStream->LastRead();
			if (bytes_read > 0) {
				buffer[bytes_read] = 0;
				wxString buffRead((const char*)buffer, wxConvUTF8);
				m_dataRead.Append(buffRead);
			}
		} while ( !httpStream->Eof() );
		wxArrayString lines = wxStringTokenize(m_dataRead, wxT("\n"));
		for (size_t i=0; i<lines.GetCount(); i++) {
			wxArrayString tokens = wxStringTokenize(lines.Item(i), wxT("|"));
			if(v2c == "application") {
				pc_v2cimportapp->Append(tokens.Item(0).Trim());
				appurlkey.Add(tokens.Item(0).Trim());
				appurlname.Add(tokens.Item(1).Trim().Trim(false));
				appurl.Add(tokens.Item(2).Trim().Trim(false));
				appurlhtml.Add(tokens.Item(3).Trim().Trim(false));
				pc_v2cimportapp->SetSelection(0);
				importhtml("application");
			} else if(v2c == "shortcut") {
				pc_v2cimportshortcut->Append(tokens.Item(0).Trim());
				shortcuturlkey.Add(tokens.Item(0).Trim());
				shortcuturlname.Add(tokens.Item(1).Trim().Trim(false));
				shortcuturl.Add(tokens.Item(2).Trim().Trim(false));
				shortcuturlhtml.Add(tokens.Item(3).Trim().Trim(false));
				pc_v2cimportshortcut->SetSelection(0);
				importhtml("shortcut");
			}
		}
	} else {
		return 0;
	}
	wxDELETE(httpStream);
	get.Close();
	return 1;
}

bool MainFrame::getv2c(wxString v2c)
{
	int index = 0;
	wxString name;
	if(v2c == "application") {
		index = appurlkey.Index(pc_v2cimportapp->GetStringSelection());
	} else if(v2c == "shortcut") {
		index = shortcuturlkey.Index(pc_v2cimportshortcut->GetStringSelection());
	}
	if(index != wxNOT_FOUND) {
		// download
		wxURI v2ccompleteurl;
		if(v2c == "application") {
			v2ccompleteurl = appurl.Item(index);
			name = appurlname.Item(index);
		} else if(v2c == "shortcut") {
			v2ccompleteurl = shortcuturl.Item(index);
			name = shortcuturlname.Item(index);
		}
		if(!downloadv2c(v2ccompleteurl.GetServer(), v2ccompleteurl.GetPath())) {
			wxMessageBox("Cannot download the list of V2C.\nMaybe the server is down or you have a connection problem.");
			return 0;
		}
		// gunzip
		if(!gunzipv2c(v2c, name)) {
			return 0;
		}
		// remove file
		if(wxFileExists(stdpath.GetTempDir()+"/v2c.gz")) {
			wxRemoveFile(stdpath.GetTempDir()+"/v2c.gz");
		}
		// shortcut merge to v2s
		if(v2c == "shortcut") {
			
			wxArrayString noti;
			wxArrayString pretrigger;
			wxArrayString trigger;
			wxArrayString command;
			wxArrayString comment;
			wxArrayString type;
			
			if(wxFileExists(GetCurrentWorkingDirectory()+"/v2c/shortcut.v2s")) {
				// shortcut.v2s
				wxFileInputStream input(GetCurrentWorkingDirectory()+"/v2c/shortcut.v2s");
				wxJSONValue  roottpm;
				wxJSONReader reader;
				int numErrors = reader.Parse( input, &roottpm );
				if ( numErrors > 0 )  {
					wxMessageBox("ERROR: the JSON document is not well-formed");
				}
				wxJSONValue modules = roottpm["Actions"];
				if (modules.IsArray() ) {
					for ( int i = 0; i < modules.Size(); i++ ) {
						noti.Add( modules[i]["Notification"].AsString() );
						pretrigger.Add( modules[i]["Pretrigger"].AsString() );
						trigger.Add( modules[i]["Trigger"].AsString() );
						command.Add( modules[i]["Command"].AsString() );
						comment.Add( modules[i]["Comment"].AsString() );
						type.Add( modules[i]["Type"].AsString() );
					}
				}
 			}
			// v2s to merge
			wxFileInputStream inputshortcut(GetCurrentWorkingDirectory() + "/v2c/" + pc_v2cimportshortcut->GetStringSelection().Lower() + ".v2s");
			wxJSONValue  roottpmshortcut;
			wxJSONReader readershortcut;
			int numErrors = readershortcut.Parse( inputshortcut, &roottpmshortcut );
			if ( numErrors > 0 )  {
				wxMessageBox("ERROR: the JSON document is not well-formed");
			}
			wxJSONValue modulesshortcut = roottpmshortcut["Actions"];
			// check if trigger already exist
			for ( unsigned int i = 0; i < trigger.GetCount(); i++ ) {
					int search = trigger[i].Index(modulesshortcut[0]["Trigger"].AsString());
					if(search != wxNOT_FOUND) {
						wxMessageBox("Looks like you already use this trigger: " + modulesshortcut[0]["Trigger"].AsString());
						return 0;
					}
			}
			noti.Add( modulesshortcut[0]["Notification"].AsString() );
			pretrigger.Add( modulesshortcut[0]["Pretrigger"].AsString() );
			trigger.Add( modulesshortcut[0]["Trigger"].AsString() );
			command.Add( modulesshortcut[0]["Command"].AsString() );
			comment.Add( modulesshortcut[0]["Comment"].AsString() );
			type.Add( modulesshortcut[0]["Type"].AsString() );
			// write shortcut.v2s
			wxJSONValue root;
			root.AddComment( "// voice2command - do not edit by hand", wxJSONVALUE_COMMENT_BEFORE );
			for(unsigned int i = 0; i < noti.GetCount(); i++) {
				wxJSONValue actions;
				actions["Notification"] = noti.Item(i);
				actions["Pretrigger"] = pretrigger.Item(i);
				actions["Trigger"] = trigger.Item(i);
				actions["Command"] = command.Item(i);
				actions["Comment"] = comment.Item(i);
				actions["Type"] = type.Item(i);
				root["Actions"].Append(actions);	
			}
			wxJSONWriter writer( wxJSONWRITER_STYLED | wxJSONWRITER_WRITE_COMMENTS );
			wxString  jsonText;
			writer.Write( root, jsonText );
			wxFile myFile(GetCurrentWorkingDirectory()+"/v2c/shortcut.v2s", wxFile::write);
			myFile.Write(jsonText);
			myFile.Close();

			// remove file
			wxRemoveFile(GetCurrentWorkingDirectory()+"/v2c/"+pc_v2cimportshortcut->GetStringSelection().Lower() + ".v2s");
		}
		// installed
		importsuccess();
		return 1;
	} else {
		return 0;
	}
}

bool MainFrame::downloadv2c(wxString server, wxString tgz)
{
	wxHTTP get;
	get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
	get.SetTimeout(10); 
	int tried = 0;
	while (!get.Connect(server)) {
		if(tried > 2) {
			return 0;
		}
		wxSleep(2);
		tried++;
	}
	wxInputStream *httpStream = get.GetInputStream(tgz);
	if (get.GetError() == wxPROTO_NOERR)
	{
		// standard path
		wxStandardPaths stdpath;
		stdpath = wxStandardPaths::Get();
		wxFileOutputStream outStream(stdpath.GetTempDir()+"/v2c.gz");
		const int DLBUFSIZE = 4096;
		unsigned char buffer[DLBUFSIZE+1];
		do {
			httpStream->Read(buffer, DLBUFSIZE);
			size_t bytes_read = httpStream->LastRead();
			if (bytes_read > 0) {
				buffer[bytes_read] = 0;
				outStream.Write(buffer, bytes_read);
			}
		} while ( !httpStream->Eof() );
		outStream.Close();
	} else {
		return 0;
	}
	wxDELETE(httpStream);
	get.Close();
	return 1;
}

bool MainFrame::gunzipv2c(wxString v2c, wxString fn)
{
	char buffer[1024];
	wxString targetname;
	wxArrayString filen;
	if(v2c == "application") {
		if(wxFileExists(GetCurrentWorkingDirectory()+"/v2c/"+fn+ ".v2a")) {
			wxMessageBox("Looks like you already have this process name defined: "+pc_v2cimportapp->GetStringSelection().Lower());
			return 0;
		} else {
			targetname = GetCurrentWorkingDirectory()+"/v2c/"+fn+".v2a";
		}
	} else if (v2c == "shortcut") {
		targetname = GetCurrentWorkingDirectory()+"/v2c/"+fn+".v2s";
	} else { // filepicker import - disabled for now
		filen.Add(v2c.AfterLast('/'));
		targetname = GetCurrentWorkingDirectory()+"/v2c/"+filen[0].Mid(0, filen[0].Length() - 3);
	}

	wxTempFile target(targetname);
	bool write = false;
	
	wxString sourcestring;
	if(v2c == "application" || v2c == "shortcut") {
		sourcestring = stdpath.GetTempDir()+"/v2c.gz";
	} else { // filepicker import
		sourcestring = v2c;
	}
	wxFileInputStream source(sourcestring);
	wxZlibInputStream inputStream(source);

	while (!inputStream.Eof()) {
			inputStream.Read(buffer, sizeof(buffer));
			if (inputStream.LastRead()) {
					target.Write(buffer, inputStream.LastRead());
			} else {
					break;
			}
	};
	write = inputStream.IsOk() || inputStream.Eof();

	if (write) {
			target.Commit();
			return 1;
	} else {
		return 0;
	}
}

void MainFrame::importsuccess()
{
	// installed
	wxMessageBox("Installed!");
	V2cApplicationLoad(); // fill the V2C panel
	V2cShortcutLoad();  // fill the V2C panel
	pspnameid.Empty(); // allow monitor to reload the application
	v2cloading();
	if(m_Julius && juliusisready) {
		juliusgentlyexit();
		startjuliusthread();
	}
}

////////////////////////////////////////////////////////////////////////////////
// EXPORT
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DICTIONARY
////////////////////////////////////////////////////////////////////////////////
void MainFrame::writedictionary()
{
	if(!juliusformat_word.GetCount()) {
		autocomplete();
	}
	// write dictionary with all words
	wxArrayString allword;

	if(cb_dict->GetValue()) { // dictionary - match v2c
	
		unsigned int i = 0;
		while(i < trigger.GetCount()) {
			if(trigger[i] != "" && allword.Index(trigger[i].Upper()) == wxNOT_FOUND) {
				allword.Add( trigger[i].Upper() );
			}
			if(pretrigger[i] != "" && allword.Index(pretrigger[i].Upper()) == wxNOT_FOUND) {
				allword.Add( pretrigger[i].Upper() );
			}
			i++;
		}

		
	} else { // dictionary - all
	
		// shortcut
		if(wxFile::Exists(GetCurrentWorkingDirectory()+"/v2c/shortcut.v2s")) {
			wxFileInputStream input(GetCurrentWorkingDirectory()+"/v2c/shortcut.v2s");
			wxJSONValue  root;
			wxJSONReader reader;
			int numErrors = reader.Parse( input, &root );
			if ( numErrors == 0 )  {
				wxJSONValue modules = root["Actions"];
				if (modules.IsArray() ) {
					for ( int i = 0; i < modules.Size(); i++ ) {
						if(allword.Index(modules[i]["Pretrigger"].AsString().Upper()) == wxNOT_FOUND && modules[i]["Pretrigger"].AsString().Upper() != "") {
							allword.Add( modules[i]["Pretrigger"].AsString().Upper() );
						}
						if(allword.Index(modules[i]["Trigger"].AsString().Upper()) == wxNOT_FOUND && modules[i]["Trigger"].AsString().Upper() != "") {
							allword.Add( modules[i]["Trigger"].AsString().Upper() );
						}
					}
				}
				if(pc_v2cshortcut->GetCount()){
					pc_v2cshortcut->SetSelection(0);
				}
			}
		}
	
		// aplication & launcher
		wxDir dir(GetCurrentWorkingDirectory()+"/v2c");
		wxString filename;
		bool cont = dir.GetFirst(&filename, "*.v2a", wxDIR_FILES);
		while ( cont )
		{
			wxFileInputStream input(GetCurrentWorkingDirectory()+"/v2c/"+filename);
			wxJSONValue  root;
			wxJSONReader reader;
			int numErrors = reader.Parse( input, &root );
			if ( numErrors > 0 )  {
				wxMessageBox("ERROR: the JSON document is not well-formed");
			}
			// application
			wxJSONValue modules = root["Actions"];
			if ( modules.IsArray() ) {
				for ( int i = 0; i < modules.Size(); i++ ) {
					if(allword.Index(modules[i]["Pretrigger"].AsString().Upper()) == wxNOT_FOUND && modules[i]["Pretrigger"].AsString().Upper() != "") {
							allword.Add( modules[i]["Pretrigger"].AsString().Upper() );
						}
						if(allword.Index(modules[i]["Trigger"].AsString().Upper()) == wxNOT_FOUND && modules[i]["Trigger"].AsString().Upper() != "") {
							allword.Add( modules[i]["Trigger"].AsString().Upper() );
					}
				}
			}
			// launcher
			if(allword.Index(root["Launcher"]["Pretrigger"].AsString().Upper()) == wxNOT_FOUND && root["Launcher"]["Pretrigger"].AsString().Upper() != "") {
				allword.Add( root["Launcher"]["Pretrigger"].AsString().Upper() );
			}
			if(allword.Index(root["Launcher"]["Trigger"].AsString().Upper()) == wxNOT_FOUND && root["Launcher"]["Trigger"].AsString().Upper() != "") {
				allword.Add( root["Launcher"]["Trigger"].AsString().Upper() );
			}
			cont = dir.GetNext(&filename);
		}
		
	}
	
	wxString finaldict;
	if(language == "en") {
		finaldict.Append("</s>	[]	sil\n");
		finaldict.Append("<s>	[]	sil\n");
	} else if(language == "jp" || language =="jp60k") {
		finaldict.Append("</s>	[]	silB\n");
		finaldict.Append("<s>	[]	silE\n");
	} else if(language == "german") {
		finaldict.Append("</s>	[]	sil\n");
		finaldict.Append("<s>	[]	sil\n");
	} else if(language == "portuguese") {
		finaldict.Append("</s>	[]	sil\n");
		finaldict.Append("<s>	[]	sil\n");
	}
	
	// match with the language dictionary
	for(unsigned int i=0; i<allword.GetCount(); i++)
	{
		if(allword.Item(i) != "NULL") {
			/*
			//long index = juliusformat_word.Index(allword.Item(i).Lower());
			//if(index != wxNOT_FOUND) {
				//finaldict.Append(juliusformat_word.Item(index)+" ["+juliusformat_word.Item(index)+"] "+juliusformat_pronoun.Item(index)+"\n");
			//} else {
				//wxMessageBox("You used a word that is not in the dictionary of the installed language: " + allword.Item(i));
			//}
			*/
			// need to look in dictionary for the pronunciation of the word
			wxFileInputStream input(stdpath.GetUserDataDir()+"/language/dict");
			wxTextInputStream text(input, "\x09", wxConvUTF8 );
			bool found = false;
			while(input.IsOk() && !input.Eof() )
			{
				wxString line = text.ReadLine();
				if(line.AfterFirst('[').BeforeFirst(']').Trim().Lower() == allword.Item(i).Lower()) {
					finaldict.Append(allword.Item(i).Upper()+" ["+allword.Item(i)+"] "+line.AfterLast(']').Trim(false)+"\n");
					found = true;
				}
			}
			if(!found) {
				wxMessageBox("You used a word that is not in the dictionary of the installed language: " + allword.Item(i));
			}
		}
	}
	
	if(finaldictprevious != finaldict) {
		// create dict (with silence)
		wxFile dictb;
		dictb.Create(GetCurrentWorkingDirectory()+"/language/dictionary", wxFile::write);
		dictb.Write(finaldict);
		finaldictprevious = finaldict;
		dictb.Close();
		
		// need to restart julius after changing dictionary
		//if(cb_dict->GetValue()) {
			if(m_Julius && juliusisready) {
				juliusgentlyexit();
				startjuliusthread();
			}
		//}
	}
}

void MainFrame::Oncb_dict( wxCommandEvent& event )
{
	writepreference();
	v2cloading();
}

void MainFrame::autocomplete()
{
	/*
	wxFileInputStream input(stdpath.GetUserDataDir()+"/language/dict");
	wxTextInputStream text(input, "\x09", wxConvUTF8 );
	while(input.IsOk() && !input.Eof() )
	{
	  wxString line = text.ReadLine();
	  juliusformat_word.push_back(line.AfterFirst('[').BeforeFirst(']').Trim().Lower());
	  juliusformat_pronoun.push_back(line.AfterLast(']').Trim(false));
	}
	*/
	/*
	wxFFile tfile;
	tfile.Open(stdpath.GetUserDataDir()+"/language/dict");
	size_t bytes_read = 4000;
	size_t bytes_readed = 0;
	unsigned char buffer[4000+1];
	while(!tfile.Eof())
	{
		fscanf(tfile, "%[^\n]", (char*)buffer);
		buffer[bytes_read] = 0;
		bytes_readed = tfile.Read((char*)buffer, bytes_read);
		wxString buffRead((const char*)buffer);
		juliusformat_word.push_back(buffRead.AfterFirst('[').BeforeFirst(']').Trim().Lower());
		juliusformat_pronoun.push_back(buffRead.AfterLast(']').Trim(false));
	}
	tfile.Close();
	wxPuts(juliusformat_word.Item(1));
	wxPuts(juliusformat_pronoun.Item(1));
	wxPuts(juliusformat_word.Item(2));
	wxPuts(juliusformat_pronoun.Item(2));
	wxPuts(juliusformat_word.Item(3));
	wxPuts(juliusformat_pronoun.Item(3));
	wxPuts(juliusformat_word.Item(4));
	wxPuts(juliusformat_pronoun.Item(4));
	*/
	/*
	wxTextFile tfile;
	tfile.Open(stdpath.GetUserDataDir()+"/language/dict");
	wxString tokenit;
	wxString lastword;
	while(!tfile.Eof())
	{
		tokenit = tfile.GetNextLine();
		// avoid duplicate
		if(lastword != tokenit.AfterFirst('[').BeforeFirst(']').Trim().Lower()) {
			juliusformat_word.push_back(tokenit.AfterFirst('[').BeforeFirst(']').Trim().Lower());
			juliusformat_pronoun.push_back(tokenit.AfterLast(']').Trim(false));
			lastword = tokenit.AfterFirst('[').BeforeFirst(']').Trim().Lower();
		}
	}
	tfile.Close();
	*/
	
	
	/*
	// problem with utf8
	wxFileInputStream input(dict);
    wxTextInputStream text( input );
	wxString tokenit;
	
    while(input.IsOk() && !input.Eof() )
    {
		tokenit = text.ReadLine();
		juliusformat_word.push_back(tokenit.AfterFirst('[').BeforeFirst(']').Trim().Lower().ToUTF8());
		wxMessageBox(tokenit);

		juliusformat_pronoun.push_back(tokenit.AfterLast(']').Trim(false));
	}
	*/
}


////////////////////////////////////////////////////////////////////////////////
// V2C LOADING
////////////////////////////////////////////////////////////////////////////////
void MainFrame::v2cloading()
{
	noti.Empty();
	pretrigger.Empty();
	trigger.Empty();
	command.Empty();
	comment.Empty();
	type.Empty();
	process.Empty();
	v2c.Empty();
	
	// monitor
	processnamepid.Empty();
	pspid.Empty();
	
	if(wxDirExists(GetCurrentWorkingDirectory()+"/v2c")) {
		// load v2s (shortcut) - always loaded
		if(wxFile::Exists(GetCurrentWorkingDirectory()+"/v2c/shortcut.v2s")) {
			wxFileInputStream input(GetCurrentWorkingDirectory()+"/v2c/shortcut.v2s");
			wxJSONValue  root;
			wxJSONReader reader;
			int numErrors = reader.Parse( input, &root );
			if ( numErrors > 0 )  {
				wxMessageBox("ERROR: the JSON document is not well-formed");
			}
			wxJSONValue modules = root["Actions"];
			if (modules.IsArray() ) {
				for ( int i = 0; i < modules.Size(); i++ ) {
					noti.Add( modules[i]["Notification"].AsString() );
					pretrigger.Add( modules[i]["Pretrigger"].AsString().Upper() );
					trigger.Add( modules[i]["Trigger"].AsString().Upper() );
					command.Add( modules[i]["Command"].AsString() );
					comment.Add( modules[i]["Comment"].AsString() );
					type.Add( modules[i]["Type"].AsString() );
					v2c.Add("v2s");
					process.Add("");
				}
			}
		}
		
		// load v2a (application)
		if(rb_v2cmethod->GetSelection() == 0) { // method all

			v2clauncher = false;
			wxDir dir(GetCurrentWorkingDirectory()+"/v2c");
			wxString filename;
			bool cont = dir.GetFirst(&filename, "*.v2a", wxDIR_FILES);
			while ( cont )
			{
				wxFileInputStream input(GetCurrentWorkingDirectory()+"/v2c/"+filename);
				wxJSONValue  root;
				wxJSONReader reader;
				int numErrors = reader.Parse( input, &root );
				if ( numErrors > 0 )  {
					wxMessageBox("ERROR: the JSON document is not well-formed");
				}
				// application
				wxJSONValue modules = root["Actions"];
				if ( modules.IsArray() ) {
					for ( int i = 0; i < modules.Size(); i++ ) {
						noti.Add( modules[i]["Notification"].AsString() );
						pretrigger.Add( modules[i]["Pretrigger"].AsString().Upper() );
						trigger.Add( modules[i]["Trigger"].AsString().Upper() );
						command.Add( modules[i]["Command"].AsString() );
						comment.Add( modules[i]["Comment"].AsString() );
						type.Add( modules[i]["Type"].AsString() );
						v2c.Add("v2a");
						process.Add(root["ProcessName"].AsString());
					}
				}
				// launcher
				noti.Add( root["Launcher"]["Notification"].AsString() );
				pretrigger.Add( root["Launcher"]["Pretrigger"].AsString().Upper() );
				trigger.Add( root["Launcher"]["Trigger"].AsString().Upper() );
				command.Add( root["Launcher"]["Command"].AsString() );
				comment.Add( root["Launcher"]["Comment"].AsString() );
				type.Add( root["Launcher"]["Type"].AsString() );
				process.Add( root["ProcessName"].AsString() );
				v2c.Add("launcher");
				cont = dir.GetNext(&filename);
			}
		
		} else { // method match

			if(cb_v2clauncher->GetValue()) { // Launcher
				v2clauncher = true;
				wxDir dir(GetCurrentWorkingDirectory()+"/v2c");
				wxString filename;
				bool cont = dir.GetFirst(&filename, "*.v2a", wxDIR_FILES);
				while ( cont )
				{
					wxFileInputStream input(GetCurrentWorkingDirectory()+"/v2c/"+filename);
					wxJSONValue  root;
					wxJSONReader reader;
					int numErrors = reader.Parse( input, &root );
					if ( numErrors > 0 )  {
						wxMessageBox("ERROR: the JSON document is not well-formed");
					}
					
					// only launcher
					noti.Add( root["Launcher"]["Notification"].AsString() );
					pretrigger.Add( root["Launcher"]["Pretrigger"].AsString().Upper() );
					trigger.Add( root["Launcher"]["Trigger"].AsString().Upper() );
					command.Add( root["Launcher"]["Command"].AsString() );
					comment.Add( root["Launcher"]["Comment"].AsString() );
					type.Add( root["Launcher"]["Type"].AsString() );
					process.Add( root["ProcessName"].AsString() );
					v2c.Add("launcher");
					cont = dir.GetNext(&filename);
				}
			} else {
				v2clauncher = false;
			}
			
			if(cb_v2cmonitor->GetValue()) { // monitor process
				v2cloadingprocessname();
				m_timer->Start(POLLING);
			}
		}
	}
	
	// write the dictionary to use
	writedictionary();
	
	#ifdef DEBUG
		unsigned int i = 0;
		while(i < trigger.GetCount()) {
			wxPuts("-----------------");
			wxPuts("Process:"+process.Item(i));
			wxPuts("Trigger:"+trigger.Item(i));
			wxPuts("V2C:"+v2c.Item(i));
			i++;
		}
	#endif
}

void MainFrame::v2cloading(wxString file, long pid)
{
    wxFileInputStream input(file);
    wxJSONValue  root;
    wxJSONReader reader;
    int numErrors = reader.Parse( input, &root );
    if ( numErrors > 0 )  {
        wxMessageBox("ERROR: the JSON apps.v2c document is not well-formed");
    }
    wxJSONValue modules = root["Actions"];
    
	if (modules.IsArray() ) {
		
		//Prepare HASH when application quit
		if(pidra.find(pid) == pidra.end()) { // to protect from loading twice (if launcher & monitor)
			pidra[pid] = noti.GetCount();
			pidcount[pid] = modules.Size();
	
			for ( int i = 0; i < modules.Size(); i++ ) {
				noti.Add( modules[i]["Notification"].AsString() );
				pretrigger.Add( modules[i]["Pretrigger"].AsString().Upper() );
				trigger.Add( modules[i]["Trigger"].AsString().Upper() );
				command.Add( modules[i]["Command"].AsString() );
				comment.Add( modules[i]["Comment"].AsString() );
				process.Add( root["ProcessName"].AsString() );
				type.Add( modules[i]["Type"].AsString() );
				v2c.Add("v2a");
			}
		}
	}
	
	// write the dictionary to use
	writedictionary();
}

void MainFrame::v2cloadingprocessname()
{
	processname.Empty();
	wxDir dir(GetCurrentWorkingDirectory()+"/v2c/");
	wxString filename;
	bool cont = dir.GetFirst(&filename, "*.v2a", wxDIR_FILES);
	while ( cont )
	{
		wxFileInputStream input(GetCurrentWorkingDirectory()+"/v2c/"+filename);
		wxJSONValue  root;
		wxJSONReader reader;
		int numErrors = reader.Parse( input, &root );
		if ( numErrors > 0 )  {
			wxMessageBox("ERROR: the JSON document is not well-formed");
		}
		
		processname.Add( root["ProcessName"].AsString() );
		#ifdef DEBUG
				wxPuts("ProcessName: "+root["ProcessName"].AsString());
		#endif
		cont = dir.GetNext(&filename);
	}
}

void MainFrame::Onrb_v2cmethod( wxCommandEvent& event )
{
	// gui work
	if(rb_v2cmethod->GetSelection() == 0) {
		cb_v2cmonitor->Enable(0);
		cb_v2clauncher->Enable(0);
		cb_v2cmonitor->SetValue(0);
		cb_v2clauncher->SetValue(0);
	} else {
		cb_v2cmonitor->Enable(1);
		cb_v2clauncher->Enable(1);
		cb_v2cmonitor->SetValue(1);
		cb_v2clauncher->SetValue(1);
	}
	
	v2cloading();
	writepreference();
}

void MainFrame::Oncb_v2cmonitor( wxCommandEvent& event )
{
	if(cb_v2cmonitor->GetValue()) {
		pspnameid.Empty(); // allow monitor to reload the application		v2cloadingprocessname();
		m_timer->Start(POLLING);
	} else {
		if(!cb_v2clauncher->GetValue()) {
			wxMessageBox("You need at least one matching method.");
			cb_v2cmonitor->SetValue(1);
		} else {
			processname.Empty();
			m_timer->Stop();
		}
	}
		writepreference();
}

void MainFrame::Oncb_v2clauncher( wxCommandEvent& event )
{
	if(!cb_v2clauncher->GetValue() && !cb_v2cmonitor->GetValue()) {
		wxMessageBox("You need at least one matching method.");
		cb_v2clauncher->SetValue(1);
	} else {
		pspnameid.Empty(); // allow monitor to reload the application
		v2cloading();
		writepreference();
	}
}

////////////////////////////////////////////////////////////////////////////////
// MONITOR PROCESS
////////////////////////////////////////////////////////////////////////////////
int MainFrame::IsNumeric(const char* ccharptr_CharacterList)
{
    for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++)
        if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
            return 0; // false
    return 1; // true
}

void MainFrame::OnMonitorTimer(wxTimerEvent& event)
{
	int bytesread;
	const int BUFFERSIZE = 1000;
	
    char chrarry_CommandLinePath[100];
    char chrarry_NameOfProcess[BUFFERSIZE];
	char chrarry_OnlyNameOfProcess[BUFFERSIZE];
    char* chrptr_StringToCompare = NULL ;
    pid_t pid_ProcessIdentifier = (pid_t) -1 ;
    struct dirent* de_DirEntity = NULL ;
    DIR* dir_proc = NULL ;
    dir_proc = opendir(PROC_DIRECTORY) ;
    if (dir_proc == NULL)
    {
        wxMessageBox("Couldn't open the " PROC_DIRECTORY " directory");
    }
	
    pspid.Empty();

    while ( (de_DirEntity = readdir(dir_proc)) )
    {
        if (de_DirEntity->d_type == DT_DIR)
        {
            if (IsNumeric(de_DirEntity->d_name))
            {
                strcpy(chrarry_CommandLinePath, PROC_DIRECTORY) ;
                strcat(chrarry_CommandLinePath, de_DirEntity->d_name) ;
                strcat(chrarry_CommandLinePath, "/cmdline") ;
                FILE* fd_CmdLineFile = fopen (chrarry_CommandLinePath, "rt") ;  // open the file for reading text
				
                if (fd_CmdLineFile)
                {
					int fsrs = fscanf(fd_CmdLineFile, "%s", chrarry_OnlyNameOfProcess) ; // read from /proc/<NR>/cmdline
					// just avoiding -Wunused-variable
					(void)fsrs;
					
					rewind(fd_CmdLineFile);
					bytesread = fread(chrarry_NameOfProcess, 1, BUFFERSIZE, fd_CmdLineFile);
					for (int i = 0; i < bytesread; ++i)
						if (chrarry_NameOfProcess[i] == '\0')
							chrarry_NameOfProcess[i] = ' ';
					chrarry_NameOfProcess[bytesread] = '\0';
					fclose(fd_CmdLineFile);
	
                    if (strrchr(chrarry_OnlyNameOfProcess, '/')) {
                        chrptr_StringToCompare = strrchr(chrarry_OnlyNameOfProcess, '/') +1;
                    } else {
                        chrptr_StringToCompare = chrarry_OnlyNameOfProcess;
						wxString stc(chrptr_StringToCompare, wxConvUTF8);
						if(stc.Find("python") != wxNOT_FOUND) {
								chrptr_StringToCompare = strrchr(chrarry_NameOfProcess, '/') +1;
						}
					}
					
					wxString stc(chrptr_StringToCompare, wxConvUTF8);
					//wxPuts("-"+stc.Trim()+"-");
					
                    //printf("Pure Process name: %s\n", chrarry_OnlyNameOfProcess );
					
                    //get the pid
                    pid_ProcessIdentifier = (pid_t) atoi(de_DirEntity->d_name) ;
                    pspid.Add(wxString::Format("%i",pid_ProcessIdentifier));
					
					//search pure process name for loaded ProcessName
					
                    int ps = processname.Index(stc.Trim());
					
					
					/*
					wxPuts("--------------------------------------------");
					for(unsigned int i = 0; i < processname.GetCount(); i++) {
						
						wxPuts(processname.Item(i));
					}
					*/
						
                    //found one
                    if(ps != wxNOT_FOUND) {
							
                            if(processnamepid.Index(wxString::Format("%i",pid_ProcessIdentifier)) == wxNOT_FOUND && pspnameid.Index(chrptr_StringToCompare) == wxNOT_FOUND) {
                                #ifdef DEBUG
									wxPuts("++++++++++++++++++++++++++++");
									wxPuts("Monitor...");
									wxPuts("File: "+GetCurrentWorkingDirectory() + "/v2c/" + processname.Item(ps) + ".v2a");
									wxPuts(wxString::Format("PID: %i", pid_ProcessIdentifier));
									wxPuts("++++++++++++++++++++++++++++");
								#endif
								
								//load associated v2c
                                v2cloading(GetCurrentWorkingDirectory()+"/v2c/"+processname.Item(ps)+".v2a", pid_ProcessIdentifier);
                                processnamepid.Add(wxString::Format("%i",pid_ProcessIdentifier));
								pspnameid.Add(processname.Item(ps)); // avoid to call this v2cloading() multiple times for the same process with multiple instance
							}

                    }
                    /*
                    if ( CompareFunction(chrptr_StringToCompare, cchrptr_ProcessName, intCaseSensitiveness) )
                    {
                        pid_ProcessIdentifier = (pid_t) atoi(de_DirEntity->d_name) ;
                        closedir(dir_proc) ;
                        return pid_ProcessIdentifier ;
                    }
                    */
                }
				
            }
        }
    }
	// if the application is not alive anymore
    if(processnamepid.GetCount()) {

        for(unsigned int i = 0; i < processnamepid.GetCount(); i++) {

            if(pspid.Index(processnamepid[i]) == wxNOT_FOUND) {

                long pid = wxAtoi(processnamepid[i]);
                processnamepid.RemoveAt(i);
				
				// to allow to reload the application
				int n = pspnameid.Index(process.Item(pidra[pid]));
				if(n != wxNOT_FOUND) {
					pspnameid.RemoveAt(n);
				}
			
                noti.RemoveAt(pidra[pid], pidcount[pid]);
                noti.Insert("", pidra[pid], pidcount[pid]);
                pretrigger.RemoveAt(pidra[pid], pidcount[pid]);
                pretrigger.Insert("", pidra[pid], pidcount[pid]);
                trigger.RemoveAt(pidra[pid], pidcount[pid]);
                trigger.Insert("", pidra[pid], pidcount[pid]);
                command.RemoveAt(pidra[pid], pidcount[pid]);
                command.Insert("", pidra[pid], pidcount[pid]);
				comment.RemoveAt(pidra[pid], pidcount[pid]);
                comment.Insert("", pidra[pid], pidcount[pid]);
                process.RemoveAt(pidra[pid], pidcount[pid]);
                process.Insert("", pidra[pid], pidcount[pid]);
                type.RemoveAt(pidra[pid], pidcount[pid]);
                type.Insert("", pidra[pid], pidcount[pid]);
				v2c.RemoveAt(pidra[pid], pidcount[pid]);
                v2c.Insert("", pidra[pid], pidcount[pid]);

				writedictionary();
            }
        }
    }
    closedir(dir_proc) ;
}

void Process::OnTerminate(int pid, int status)
{
    if(pidra.find(pid) != pidra.end()) {
        if(v2clauncher) {
			if(noti.GetCount()) {
				
				// to allow to reload the application
				int n = pspnameid.Index(process.Item(pidra[pid]));
				if(n != wxNOT_FOUND) {
					pspnameid.RemoveAt(n);
				}
				
				noti.RemoveAt(pidra[pid], pidcount[pid]);
				noti.Insert("", pidra[pid], pidcount[pid]);
				pretrigger.RemoveAt(pidra[pid], pidcount[pid]);
				pretrigger.Insert("", pidra[pid], pidcount[pid]);
				trigger.RemoveAt(pidra[pid], pidcount[pid]);
				trigger.Insert("", pidra[pid], pidcount[pid]);
				command.RemoveAt(pidra[pid], pidcount[pid]);
				command.Insert("", pidra[pid], pidcount[pid]);
				comment.RemoveAt(pidra[pid], pidcount[pid]);
				comment.Insert("", pidra[pid], pidcount[pid]);
				process.RemoveAt(pidra[pid], pidcount[pid]);
				process.Insert("", pidra[pid], pidcount[pid]);
				type.RemoveAt(pidra[pid], pidcount[pid]);
				type.Insert("", pidra[pid], pidcount[pid]);
				v2c.RemoveAt(pidra[pid], pidcount[pid]);
				v2c.Insert("", pidra[pid], pidcount[pid]);
			}
        }
    }
	m_parent->writedictionary();
    // we're not needed any more
    delete this;
}

////////////////////////////////////////////////////////////////////////////////
// LANGUAGE
////////////////////////////////////////////////////////////////////////////////
void MainFrame::OnLanguageProgess(int bs, int ts)
{
	g_languagedownloading->SetRange(ts);
	g_languagedownloading->SetValue(bs);
	wxYield(); // until socket thread is fixed
}

void MainFrame::Onb_languagedownload( wxCommandEvent& event )
{	
	c_language->Enable(0);
	b_languagedownload->Enable(0);
	st_languagedownloading->Show(1);
	g_languagedownloading->Show(1);
	
	// download and (install or update)
	if(!languagedownload()) {
		c_language->Enable(1);
		b_languagedownload->Enable(1);
		st_languagedownloading->Show(0);
		g_languagedownloading->Show(0);
	};
}

bool MainFrame::languagedownload() {
	
	m_pLanguage = new Language(this);

	// where to download the language
	wxString server, tgz;
	if(c_language->GetStringSelection() == "English 14k [VoxForge]") {
		//server = "voxforge.com";
		//tgz = "/downloads/Nightly_Builds/current/HTK_AcousticModel-2010-12-16_16kHz_16bit_MFCC_O_D.tgz";
		server = "cloud.github.com";
		tgz = "/downloads/patricksebastien/kiku/EnglishAM14k.tar.gz";
	} else if(c_language->GetStringSelection() == "Japanese 20k [Julius]") {
		server = "julius.sourceforge.jp";
		tgz = "/archive/japanese-models.tar.gz";
	} else if(c_language->GetStringSelection() == "Japanese 60k [Julius]") {
		//server = "iij.dl.sourceforge.jp";
		//tgz = "/julius/51158/dictation-kit-v4.1.tar.gz";
		server = "cloud.github.com";
		tgz = "/downloads/patricksebastien/kiku/JapaneseAM60k.tar.gz";
	} else if(c_language->GetStringSelection() == "German 370k [VoxForge]") {
		server = "cloud.github.com";
		tgz = "/downloads/patricksebastien/kiku/GermanAM370k.tar.gz";
	} else if(c_language->GetStringSelection() == "Portuguese 65k [Fala Brasil]") {
		server = "cloud.github.com";
		tgz = "/downloads/patricksebastien/kiku/PortugueseAM65k.tar.gz";
	}

	// 1) download
	if(!m_pLanguage->download(server, tgz)) {
		wxMessageBox("Cannot download the language file.\nMaybe the server is down or you have a connection problem.");
		return 0;
	}
		
	// 2) gunzip
	g_languagedownloading->Pulse();
	wxYield();
	st_languagedownloading->SetLabel("Installing...");
	if(!m_pLanguage->gunzip(stdpath.GetTempDir()+"/model.tar", stdpath.GetTempDir()+"/model.tar.gz")) {
		wxMessageBox("Cannot gunzip the language file.");
		return 0;
	}
	
	// 3) untar
	g_languagedownloading->Pulse();
	wxYield();
			
	if(!m_pLanguage->untar(stdpath.GetTempDir()+"/model.tar", GetCurrentWorkingDirectory()+"/language/")) {
		wxMessageBox("Cannot untar the language file.");
		return 0;
	}
	
	// exceptions: (binary for voxforge) / (gunzip dictionary if japanese) 
	if(c_language->GetStringSelection() == "English 14k [VoxForge]") {
		
		wxString cp;
		wxArrayString output, errors;
		int code = wxExecute("which kiku_mkbinhmm", output, errors);
		if ( code != -1 )
		{
			if(!output.IsEmpty()) {
				cp = output[0];
			}
		}
		if(cp == "") {
			wxMessageBox("kiku_mkbinhmm / kiku_mkbinhmmlist is not installed on your system. will not make a binary version of the acoustic model.");
			wxRenameFile(GetCurrentWorkingDirectory()+"/language/hmmdefs", GetCurrentWorkingDirectory()+"/language/hmmdefsbin");
			wxRenameFile(GetCurrentWorkingDirectory()+"/language/tiedlist", GetCurrentWorkingDirectory()+"/language/tiedlistbin");
		} else {
			wxArrayString output, errors;
			wxExecute("kiku_mkbinhmm -htkconf "+GetCurrentWorkingDirectory()+"/language/wav_config "+GetCurrentWorkingDirectory()+"/language/hmmdefs "+GetCurrentWorkingDirectory()+"/language/hmmdefsbin", output, errors);
			wxExecute("kiku_mkbinhmmlist "+GetCurrentWorkingDirectory()+"/language/hmmdefsbin "+GetCurrentWorkingDirectory()+"/language/tiedlist "+GetCurrentWorkingDirectory()+"/language/tiedlistbin", output, errors);
			wxRemoveFile(GetCurrentWorkingDirectory()+"/language/hmmdefs");
			wxRemoveFile(GetCurrentWorkingDirectory()+"/language/tiedlist");
		}
		
		// remove unnecessary file
		wxRemoveFile(GetCurrentWorkingDirectory()+"/language/master_prompts");
		
	} else if(c_language->GetStringSelection() == "Japanese 20k [Julius]") {
		g_languagedownloading->Pulse();
		wxYield();
		if(!m_pLanguage->gunzip(GetCurrentWorkingDirectory()+"/language/dicteucjp", GetCurrentWorkingDirectory()+"/language/japanese-models/lang_m/20k.htkdic.gz")) {
			wxMessageBox("Cannot gunzip the language file.");
			return 0;
		}
		g_languagedownloading->Pulse();
		wxYield();
		
		// check for iconv
		wxString cp;
		wxArrayString output, errors;
		int code = wxExecute("which iconv", output, errors);
		if ( code != -1 )
		{
			if(!output.IsEmpty()) {
				cp = output[0];
			}
		}
		if(cp == "") {
			wxMessageBox("iconv is not installed on your system! sudo apt-get install libc-bin and retry.");
		} else {
			// using iconv to convert from euc-jp to utf8
			wxArrayString outputic, errorsic;
			wxExecute("iconv --from-code=EUC-JP --to-code=UTF8 -o "+GetCurrentWorkingDirectory()+"/language/dict "+GetCurrentWorkingDirectory()+"/language/dicteucjp", outputic, errorsic);
			wxRemoveFile(GetCurrentWorkingDirectory()+"/language/dicteucjp");
		}
	} else if(c_language->GetStringSelection() == "Japanese 60k [Julius]") {

		//mv file
		wxRenameFile(GetCurrentWorkingDirectory()+"/language/JapaneseAM60k/lang_m/web.60k.htkdic", GetCurrentWorkingDirectory()+"/language/dicteucjp");
		
		//convert
		// check for iconv
		wxString cp;
		wxArrayString output, errors;
		int code = wxExecute("which iconv", output, errors);
		if ( code != -1 )
		{
			if(!output.IsEmpty()) {
				cp = output[0];
			}
		}
		if(cp == "") {
			wxMessageBox("iconv is not installed on your system! sudo apt-get install libc-bin and retry.");
		} else {
			// using iconv to convert from euc-jp to utf8
			wxArrayString outputic, errorsic;
			wxExecute("iconv --from-code=SHIFT_JIS --to-code=UTF8 -o "+GetCurrentWorkingDirectory()+"/language/dict "+GetCurrentWorkingDirectory()+"/language/dicteucjp", outputic, errorsic);
			wxRemoveFile(GetCurrentWorkingDirectory()+"/language/dicteucjp");
		}
	} else if(c_language->GetStringSelection() == "German 370k [VoxForge]") {
		
		wxString cp;
		wxArrayString output, errors;
		int code = wxExecute("which kiku_mkbinhmm", output, errors);
		if ( code != -1 )
		{
			if(!output.IsEmpty()) {
				cp = output[0];
			}
		}
		if(cp == "") {
			wxMessageBox("kiku_mkbinhmm / kiku_mkbinhmmlist is not installed on your system. will not make a binary version of the acoustic model.");
			wxRenameFile(GetCurrentWorkingDirectory()+"/language/hmmdefs", GetCurrentWorkingDirectory()+"/language/hmmdefsbin");
			wxRenameFile(GetCurrentWorkingDirectory()+"/language/tiedlist", GetCurrentWorkingDirectory()+"/language/tiedlistbin");
		} else {
			wxArrayString output, errors;
			wxExecute("kiku_mkbinhmm "+GetCurrentWorkingDirectory()+"/language/hmmdefs "+GetCurrentWorkingDirectory()+"/language/hmmdefsbin", output, errors);
			wxExecute("kiku_mkbinhmmlist "+GetCurrentWorkingDirectory()+"/language/hmmdefsbin "+GetCurrentWorkingDirectory()+"/language/tiedlist "+GetCurrentWorkingDirectory()+"/language/tiedlistbin", output, errors);
			wxRemoveFile(GetCurrentWorkingDirectory()+"/language/hmmdefs");
			wxRemoveFile(GetCurrentWorkingDirectory()+"/language/tiedlist");
		}
		
	} else if(c_language->GetStringSelection() == "Portuguese 65k [Fala Brasil]") {
		
		wxString arch;
		arch = wxPlatformInfo::Get().GetArchName();
		if(arch == "64 bit") {
			wxRenameFile(GetCurrentWorkingDirectory()+"/language/hmmdefs-64bits.bin", GetCurrentWorkingDirectory()+"/language/hmmdefsbin");
			wxRemoveFile(GetCurrentWorkingDirectory()+"/language/hmmdefs-32bits.bin");
		} else {
			wxRenameFile(GetCurrentWorkingDirectory()+"/language/hmmdefs-32bits.bin", GetCurrentWorkingDirectory()+"/language/hmmdefsbin");
			wxRemoveFile(GetCurrentWorkingDirectory()+"/language/hmmdefs-64bits.bin");
		}
		wxRenameFile(GetCurrentWorkingDirectory()+"/language/tiedlist", GetCurrentWorkingDirectory()+"/language/tiedlistbin");

	}
	
	
	// 4) remove model.tar.gz & model.tar
	g_languagedownloading->Pulse();
	wxYield();
	
	if(wxFileExists(stdpath.GetTempDir()+"/model.tar.gz")) {
		wxRemoveFile(stdpath.GetTempDir()+"/model.tar.gz");
	}
	if(wxFileExists(stdpath.GetTempDir()+"/model.tar")) {
		wxRemoveFile(stdpath.GetTempDir()+"/model.tar");
	}

	////////////////////////////
	// if update don't recreate
	////////////////////////////
	if(!wxFileExists(GetCurrentWorkingDirectory()+"/language/dictionary")) {
		
		// create julius.conf
		wxFile myFile(GetCurrentWorkingDirectory()+"/language/julius.conf", wxFile::write);
		if(c_language->GetStringSelection() == "English 14k [VoxForge]") {
			myFile.Write("-w dictionary\n");
			myFile.Write("-wsil sil sil NULL\n");
			myFile.Write("-h hmmdefsbin\n");
			myFile.Write("-hlist tiedlistbin\n");
			myFile.Write("-spmodel \"sp\"\n");
		} else if(c_language->GetStringSelection() == "Japanese 20k [Julius]") {
			myFile.Write("-w dictionary\n");
			myFile.Write("-wsil silB silE NULL\n");
			myFile.Write("-h japanese-models/phone_m/hmmdefs_ptm_gid.gz\n");
			myFile.Write("-hlist japanese-models/phone_m/logicalTriList\n");
			myFile.Write("-spmodel \"sp\"\n");	
		} else if(c_language->GetStringSelection() == "Japanese 60k [Julius]") {
			myFile.Write("-w dictionary\n");
			myFile.Write("-wsil silB silE NULL\n");
			myFile.Write("-h JapaneseAM60k/phone_m/hmmdefs_ptm_gid.binhmm\n");
			myFile.Write("-hlist JapaneseAM60k/phone_m/logicalTri\n");
			myFile.Write("-spmodel \"sp\"\n");	
		} else if(c_language->GetStringSelection() == "German 370k [VoxForge]") {
			myFile.Write("-w dictionary\n");
			myFile.Write("-wsil sil sil NULL\n");
			myFile.Write("-h hmmdefsbin\n");
			myFile.Write("-hlist tiedlistbin\n");
			myFile.Write("-spmodel \"sp\"\n");
		} else if(c_language->GetStringSelection() == "Portuguese 65k [Fala Brasil]") {
			myFile.Write("-w dictionary\n");
			myFile.Write("-wsil sil sil sil\n");
			myFile.Write("-h hmmdefsbin\n");
			myFile.Write("-hlist tiedlistbin\n");
			myFile.Write("-spmodel \"sp\"\n");
		}
		
		
		myFile.Write("-gprune safe\n");
		myFile.Write("-sb 200.0\n");
		myFile.Write("-iwsp\n");
		myFile.Write("-iwsppenalty -70.0\n");
		myFile.Write("-multipath\n");
		myFile.Write("-plugindir /usr/lib/kiku\n");
		myFile.Write("-input pulseaudio-libpd\n");
		myFile.Write("-smpFreq 16000\n");
		myFile.Write("-iwcd1 avg\n");
		myFile.Write("-tmix 4\n");
		myFile.Write("-penalty1 10.0\n");
		myFile.Write("-b 14000\n");
		myFile.Write("-zmeanframe\n");
		myFile.Write("#-zc\n");	
		myFile.Write("#-lv\n");	
		myFile.Close();

		g_languagedownloading->Pulse();
		wxYield();
		
		// create dict (silence)
		wxFile dict;
		dict.Create(GetCurrentWorkingDirectory()+"/language/dictionary", wxFile::write);
		if(c_language->GetStringSelection() == "English 14k [VoxForge]") {
			language = "en";
			dict.Write("</s>	[]	sil\n");
			dict.Write("<s>	[]	sil\n");
			dict.Write("GIVE            [GIVE]          g ih v\n");
		} else if(c_language->GetStringSelection() == "Japanese 20k [Julius]") {
			language = "jp";
			dict.Write("</s>	[]	silE\n");
			dict.Write("<s>	[]	silB\n");
			dict.Write("寄付	[寄付]	k i f u \n");
		} else if(c_language->GetStringSelection() == "Japanese 60k [Julius]") {
			language = "jp60k";
			dict.Write("</s>	[]	silE\n");
			dict.Write("<s>	[]	silB\n");
			dict.Write("寄付	[寄付]	k i f u \n");
		} else if(c_language->GetStringSelection() == "German 370k [VoxForge]") {
			language = "german";
			dict.Write("</s>	[]	sil\n");
			dict.Write("<s>	[]	sil\n");
			dict.Write("GEBEN		[geben]		g e: b @ n\n");
		} else if(c_language->GetStringSelection() == "Portuguese 65k [Fala Brasil]") {
			language = "portuguese";
			dict.Write("</s>	[]	sil\n");
			dict.Write("<s>	[]	sil\n");
			dict.Write("dar  [dar]  d a X\n");
		}		
		dict.Close();
		
		// turn on juliusthread
		writepreference(); // for writing language
		startjuliusthread();
		
		// enable notebook
		p_recognition->Enable(1);
		p_V2C->Enable(1);
		p_configutation->Enable(1);
		p_engine->Enable(1);
		p_audio->Enable(1);
		
		// gui stuff
		st_languagedownloading->Show(0);
		g_languagedownloading->Show(0);
		c_language->Show(0);
		b_languagedownload->Show(0);
		st_language_select->SetLabel(c_language->GetStringSelection());
		
		// gui & html loadpage (other documentation when language is installed)
		if(c_language->GetStringSelection() == "English 14k [VoxForge]") {
			html_language->LoadPage("http://www.workinprogress.ca/KIKU/help/language_firstinstalled.html");
		} else if(c_language->GetStringSelection() == "Japanese 20k [Julius]" || c_language->GetStringSelection() == "Japanese 60k [Julius]") {
			html_language->LoadPage("http://www.workinprogress.ca/KIKU/help/language_firstinstalled_jp.html");
		} else if(c_language->GetStringSelection() == "German 370k [VoxForge]") {
			html_language->LoadPage("http://www.workinprogress.ca/KIKU/help/language_firstinstalled_german.html");
		} else if(c_language->GetStringSelection() == "Portuguese 65k [Fala Brasil]") {
			html_language->LoadPage("http://www.workinprogress.ca/KIKU/help/language_firstinstalled_portuguese.html");
		}
		
	} else { // not an update
		
		st_languagedownloading->Show(0);
		g_languagedownloading->Show(0);
		b_languagedownload->Show(0);
		
	}
	return 1;
}
/*
void MainFrame::languagedownloaderexit()
{
	{
		wxCriticalSectionLocker enter(m_pLanguageDownloaderCS);
		if (m_pLanguageDownloaderThread)
		{
			if (m_pLanguageDownloaderThread->Delete() != wxTHREAD_NO_ERROR )
				wxLogError(_("Can't delete the thread!"));
		}
	}
	while (1)
	{
		{
			wxCriticalSectionLocker enter(m_pLanguageDownloaderCS);
			if (!m_pLanguageDownloaderThread) break;
		}
		// wait for thread completion
		wxThread::This()->Sleep(1);
	}
	#ifdef DEBUG
		printf("Exiting LanguageDownloader\n");
	#endif
}
*/



////////////////////////////////////////////////////////////////////////////////
// LIBLO
////////////////////////////////////////////////////////////////////////////////
void MainFrame::EnableOSC() {
	wxString host, port;
	int protocol;
	host = tc_oschost->GetValue();
	port = wxString::Format("%i",sp_oscport->GetValue());
	if(c_oscprotocol->GetStringSelection() == "UDP") {
		protocol = LO_UDP;
	} else if(c_oscprotocol->GetStringSelection() == "TCP") {
		protocol = LO_TCP;
	} else if(c_oscprotocol->GetStringSelection() == "UNIX") {
		protocol = LO_UNIX;
	} else {
		protocol = LO_UDP;
	}
	osc = lo_address_new_with_proto(protocol, host.mb_str(), port.mb_str());
}

void MainFrame::Oncb_oscenable(wxCommandEvent& event)
{
	if(cb_oscenable->GetValue()) {
		EnableOSC();
        sp_oscport->Enable(1);
		c_oscprotocol->Enable(1);
		tc_oschost->Enable(1);
		cb_oscrecognition->Enable(1);
	} else {
		lo_address_free(osc);
		sp_oscport->Enable(0);
		c_oscprotocol->Enable(0);
		tc_oschost->Enable(0);
		cb_oscrecognition->Enable(0);
	}
	writepreference();
}



////////////////////////////////////////////////////////////////////////////////
// QUITTING
////////////////////////////////////////////////////////////////////////////////
MainFrame::~MainFrame()
{
}

void MainFrame::OnCloseFrame(wxCloseEvent& event)
{
	OnQuit();
}

void MainFrame::OnQuit()
{
	wxSocketBase::Shutdown();
	xdo_free(xdo);
	if(cb_oscenable->GetValue()) {
		lo_address_free(osc);
	}
	delete m_taskBarIcon;
	delete m_timer;
	delete reseticonm_timer;
	delete unpausem_timer;
	if(!freshinstall) {
		webexit();
	}
	if(m_Julius && juliusisready) {
		juliusgentlyexit();
	} 
	Destroy();
}

void MainFrame::webexit()
{
	{
		wxCriticalSectionLocker enter(m_pWebCS);
		if (m_pWebThread)
		{
			if (m_pWebThread->Delete() != wxTHREAD_NO_ERROR ) {
				wxLogError(_("Can't delete the thread!"));
			}
		}
	}
	while (1)
	{
		{
			wxCriticalSectionLocker enter(m_pWebCS);
			if (!m_pWebThread) break;
		}
		// wait for thread completion
		wxThread::This()->Sleep(1);
	}
	#ifdef DEBUG
		printf("Exiting web\n");
	#endif
}

void MainFrame::juliusgentlyexit()
{
	if(m_Julius && juliusisready) {
		m_Julius->resume_recognition();
		usleep(10000);
		m_Julius->stop_recognition();
	}
	{
		wxCriticalSectionLocker enter(m_pThreadCS);
		if (m_pThread)
		{
			if (m_pThread->Delete() != wxTHREAD_NO_ERROR ) {
				wxLogError(_("Can't delete the thread!"));
			}
		}
	}
	while (1)
	{
		{
			wxCriticalSectionLocker enter(m_pThreadCS);
			if (!m_pThread) break;
		}
		// wait for thread completion
		wxThread::This()->Sleep(1);
	}
	#ifdef DEBUG
		printf("Exiting kiku\n");
	#endif
}

/*
void MainFrame::startlanguagedownloaderthread()
{
	m_pLanguageDownloaderThread = new LanguageDownloader(this);

	if ( m_pLanguageDownloaderThread->Create() != wxTHREAD_NO_ERROR )
	{
		wxLogError(_("Can't create the thread!"));
		delete m_pLanguageDownloaderThread;
		m_pLanguageDownloaderThread = NULL;
	}
	else
	{
		if (m_pLanguageDownloaderThread->Run() != wxTHREAD_NO_ERROR )
		{
			wxLogError(_("Can't create the thread!"));
			delete m_pLanguageDownloaderThread;
			m_pLanguageDownloaderThread = NULL;
		}
	}
}
*/

////////////////////////////////////////////////////////////////////////////////
// WEB UPDATE
////////////////////////////////////////////////////////////////////////////////
void MainFrame::startwebthread(wxString what)
{
	m_pWebThread = new Web(this, what);

	if ( m_pWebThread->Create() != wxTHREAD_NO_ERROR )
	{
		wxLogError(_("Can't create the thread!"));
		delete m_pWebThread;
		m_pWebThread = NULL;
	}
	else
	{
		if (m_pWebThread->Run() != wxTHREAD_NO_ERROR )
		{
			wxLogError(_("Can't create the thread!"));
			delete m_pWebThread;
			m_pWebThread = NULL;
		}
	}
}

void MainFrame::OnWeb(wxCommandEvent& event)
{
	// set link
	updateurl = event.GetString();
	
	// show update icon in taskbar
	webupdateicon = true;
	haveupdate = true;
	
	// show update button
	bm_update->SetBitmap(*iconpng[1]);
	bm_update->Show(1);
	b_update->Show(1);
	kiku->Layout();
	kiku->Fit();
}

void MainFrame::Onb_update( wxCommandEvent& event )
{
	wxLaunchDefaultBrowser(updateurl);
	OnQuit();
}

////////////////////////////////////////////////////////////////////////////////
// JULIUS
////////////////////////////////////////////////////////////////////////////////
void MainFrame::startjuliusthread()
{
	juliusisready = false;

	icontb.CopyFromBitmap( *iconpng[5] );
	if (!m_taskBarIcon->SetIcon( icontb )) {
		wxMessageBox(wxT("Could not set icon."));
	}

	// statusbar
	sb->SetStatusText("Loading configuration.", 0);
	
	// fetch language/julius.conf
	readjuliusconf();
	
	m_pThread = new JuliusThread(this);

	if ( m_pThread->Create() != wxTHREAD_NO_ERROR )
	{
		wxLogError(_("Can't create the thread!"));
		delete m_pThread;
		m_pThread = NULL;
	}
	else
	{
		if (m_pThread->Run() != wxTHREAD_NO_ERROR )
		{
			wxLogError(_("Can't create the thread!"));
			delete m_pThread;
			m_pThread = NULL;
		}
	}
}

void MainFrame::startjulius()
{
	m_Julius = new Julius(this);
	m_Julius->start_recognition();
	
}


// regex TODO optimisation
int MainFrame::regexonlyint(wxString conftxt)
{	
	onlyint.Compile("([0-9]+)");
    if ( onlyint.Matches(conftxt) )
    {
        return wxAtoi(onlyint.GetMatch(conftxt));
    } else {
        return 0;
    }
}

// fetch language/julius.conf
void MainFrame::readjuliusconf()
{
    wxFileInputStream input(GetCurrentWorkingDirectory()+"/language/julius.conf");
    wxTextInputStream text( input );
    wxString line;

    while(input.IsOk() && !input.Eof() )
    {
        wxString line=text.ReadLine();

        if(line.Find(wxT("#-lv")) >= 0) {
            cb_engdefault->SetValue(1);
            sp_engthreshold->Enable(0);
            //s_englevel->Enable(0);
			//s_englevel->SetValue(2000);
			sp_engzero->SetValue(60);
			sp_engthreshold->SetValue(2000);
        } else if(line.Find(wxT("-lv")) >= 0) {
            sp_engthreshold->SetValue(regexonlyint(line));
            //s_englevel->SetValue(regexonlyint(line));
        }

        if(line.Find(wxT("#-zc")) >= 0) {
            sp_engzero->Enable(0);
        } else if(line.Find(wxT("-zc")) >= 0) {
            sp_engzero->SetValue(regexonlyint(line));
        }

		/*
        if(line.Find(wxT("#-nostrip")) >= 0) {
            cb_engnostrip->SetValue(0);
        } else if(line.Find(wxT("-nostrip")) >= 0) {
            cb_engnostrip->SetValue(1);
        }
		*/

        if(line.Find(wxT("#-zmeanframe")) >= 0) {
            cb_engzmean->SetValue(0);
        } else if(line.Find(wxT("-zmeanframe")) >= 0) {
            cb_engzmean->SetValue(1);
        }

        if(line.Find(wxT("-gprune")) >= 0) {
            if(line.Find(wxT("#-gprune")) >= 0) {
				//TODO
            } else {
                if(line.Find(wxT("safe")) >= 0) {
                    c_enggprune->SetStringSelection("safe");
                } else if(line.Find(wxT("heuristic")) >= 0) {
                    c_enggprune->SetStringSelection("heuristic");
                } else if(line.Find(wxT("beam")) >= 0) {
                    c_enggprune->SetStringSelection("beam");
                } else if(line.Find(wxT("none")) >= 0) {
                    c_enggprune->SetStringSelection("none");
                }
            }
        }

        if(line.Find(wxT("-iwcd1")) >= 0) {
            if(line.Find(wxT("#-iwcd1")) >= 0) {
            } else {
                if(line.Find("best") >= 0) {
                    sp_engiwcd1->SetValue(regexonlyint(line.SubString(7, line.Length())));
                    c_engiwcd1->SetStringSelection("best");
                } else {
                    if(line.Find("max") >= 0) {
                        c_engiwcd1->SetStringSelection("max");
                        sp_engiwcd1->Enable(0);
                    } else if(line.Find("avg") >= 0) {
                        c_engiwcd1->SetStringSelection("avg");
                        sp_engiwcd1->Enable(0);
                    }
                }
            }
        }

        if(line.Find(wxT("-tmix")) >= 0) {
            if(line.Find(wxT("#-tmix")) >= 0) {
                sp_engtmix->SetValue(0);
            } else {
                sp_engtmix->SetValue(wxString::Format("%i",regexonlyint(line)));
            }
        }

        if(line.Find(wxT("-b ")) >= 0) {
            if(line.Find(wxT("#-b")) >= 0) {
				//TODO default?
            } else {
                sp_engbeam->SetValue(wxString::Format("%i",regexonlyint(line)));
            }
        }

        if(line.Find(wxT("-penalty1")) >= 0) {
            if(line.Find(wxT("#-penalty1")) >= 0) {
				//TODO default?
            } else {
				tc_engpenalty->ChangeValue(line.Mid(10,4));
            }
        }
		
		if(line.Find(wxT("-input")) >= 0) {
				if(line == "-input pulseaudio-libpd") {
					c_driver->SetStringSelection("PulseAudio");
				} else if(line == "-input pulseaudio-libpd-monitor") {
					c_driver->SetStringSelection("PulseAudio (monitor)");
				} else if(line == "-input mic") {
					c_driver->SetStringSelection("Alsa");
				}
        }
		
    }
}

void MainFrame::writejuliusconf(wxString opt)
{
    wxTextFile juliusconftxt;
    juliusconftxt.Open(GetCurrentWorkingDirectory()+"/language/julius.conf");
    wxString line;
    bool found = FALSE;

    //level threshold
    if(opt == "lvauto") {

        for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
        {

            if(line.Find("#-lv") >= 0 || line.Find("-lv") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.InsertLine("#-lv", juliusconftxt.GetCurrentLine());
            }

            if(line.Find("#-zc") >= 0 || line.Find("-zc") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.InsertLine("#-zc", juliusconftxt.GetCurrentLine());
            }

        }

    } else if(opt == "lv") {

        for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
        {

            if(line.Find("#-lv") >= 0 || line.Find("-lv") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.InsertLine("-lv " + wxString::Format("%i",sp_engthreshold->GetValue()), juliusconftxt.GetCurrentLine());
                found = TRUE;
                break;
            }

        }
        if(!found) {
            juliusconftxt.AddLine("-lv " + wxString::Format("%i",sp_engthreshold->GetValue()));
        }

    } else if(opt == "zc") {

        for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
        {

            if(line.Find("#-zc") >= 0 || line.Find("-zc") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.InsertLine("-zc " + wxString::Format("%i",sp_engzero->GetValue()), juliusconftxt.GetCurrentLine());
                found = TRUE;
                break;
            }

        }
        if(!found) {
            juliusconftxt.AddLine("-zc " + wxString::Format("%i",sp_engzero->GetValue()));
        }
	} else if(opt == "ssload") {

        for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
        {

            if(line.Find("#-ssload") >= 0 || line.Find("-ssload") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.InsertLine("-ssload mkss", juliusconftxt.GetCurrentLine());
                found = TRUE;
                break;
            }

        }
        if(!found) {
            juliusconftxt.AddLine("-ssload mkss");
        }
	/*
    } else if(opt == "nostrip") {

        if(cb_engnostrip->GetValue()) {

            for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
            {

                if(line.Find("#-nostrip") >= 0 || line.Find("-nostrip") >= 0) {
                    juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                    juliusconftxt.InsertLine("-nostrip", juliusconftxt.GetCurrentLine());
                    found = TRUE;
                    break;
                }

            }
            if(!found) {
                juliusconftxt.AddLine("-nostrip");
            }

        } else {

            for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
            {

                if(line.Find("#-nostrip") >= 0 || line.Find("-nostrip") >= 0) {
                    juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                    juliusconftxt.InsertLine("#-nostrip", juliusconftxt.GetCurrentLine());
                    break;
                }

            }

        }
	*/
    } else if(opt == "zmean") {

        if(cb_engzmean->GetValue()) {

            for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
            {

                if(line.Find("#-zmeanframe") >= 0 || line.Find("-zmeanframe") >= 0) {
                    juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                    juliusconftxt.InsertLine("-zmeanframe", juliusconftxt.GetCurrentLine());
                    found = TRUE;
                    break;
                }

            }
            if(!found) {
                juliusconftxt.AddLine("-zmeanframe");
            }

        } else {

            for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
            {

                if(line.Find("#-zmeanframe") >= 0 || line.Find("-zmeanframe") >= 0) {
                    juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                    juliusconftxt.InsertLine("#-zmeanframe", juliusconftxt.GetCurrentLine());
                    break;
                }

            }

        }

    } else if(opt == "gprune") {

        for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
        {
            if(line.Find("-gprune") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.GoToLine(juliusconftxt.GetCurrentLine()-1);
            }
        }
        juliusconftxt.AddLine("-gprune " + c_enggprune->GetStringSelection());


    } else if(opt == "iwcd") {

        for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
        {
            if(line.Find("-iwcd1") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.GoToLine(juliusconftxt.GetCurrentLine()-1);
            }
        }
        juliusconftxt.AddLine("-iwcd1 " + c_engiwcd1->GetStringSelection());

    } else if(opt == "iwcdbest") {

        for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
        {
            if(line.Find("-iwcd1") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.GoToLine(juliusconftxt.GetCurrentLine()-1);
            }
        }
        juliusconftxt.AddLine("-iwcd1 best " + wxString::Format("%i",sp_engiwcd1->GetValue()));


    } else if(opt == "tmix") {

        for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
        {
            if(line.Find("-tmix") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.GoToLine(juliusconftxt.GetCurrentLine()-1);
            }
        }
        if(sp_engtmix->GetValue() == 0) {
            juliusconftxt.AddLine("#-tmix");
        } else {
            juliusconftxt.AddLine("-tmix " + wxString::Format("%i",sp_engtmix->GetValue()));
        }


    } else if(opt == "beam") {

        for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
        {
            if(line.Find("-b ") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.GoToLine(juliusconftxt.GetCurrentLine()-1);
            }
        }
	
        juliusconftxt.AddLine("-b " + wxString::Format("%i",sp_engbeam->GetValue()));
		
	} else if(opt == "beammax") {

        for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
        {
            if(line.Find("-b ") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.GoToLine(juliusconftxt.GetCurrentLine()-1);
            }
        }
	
        juliusconftxt.AddLine("-b max");

    } else if(opt == "penalty") {

        for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
        {
            if(line.Find("-penalty") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.GoToLine(juliusconftxt.GetCurrentLine()-1);
            }
        }
        if(tc_engpenalty->GetValue() == "") {
            juliusconftxt.AddLine("#-penalty1");
        } else {
            juliusconftxt.AddLine("-penalty1 " + tc_engpenalty->GetValue());
        }

    } else if(opt == "driver") {

        for ( line = juliusconftxt.GetFirstLine(); !juliusconftxt.Eof(); line = juliusconftxt.GetNextLine() )
        {
            if(line.Find("-input") >= 0) {
                juliusconftxt.RemoveLine(juliusconftxt.GetCurrentLine());
                juliusconftxt.GoToLine(juliusconftxt.GetCurrentLine()-1);
            }
        }
		if(c_driver->GetStringSelection() == "PulseAudio") {
			juliusconftxt.AddLine("-input pulseaudio-libpd");
		} else if(c_driver->GetStringSelection() == "PulseAudio (monitor)") {
			juliusconftxt.AddLine("-input pulseaudio-libpd-monitor");
		} else if(c_driver->GetStringSelection() == "Alsa") {
			juliusconftxt.AddLine("-input mic");
		}
		
    }

    juliusconftxt.Write();
    juliusconftxt.Close();
}

/*
void MainFrame::Ons_englevel(wxScrollEvent& event)
{
	int d = event.GetInt();
    sp_engthreshold->SetValue(d);
	writejuliusconf("lv");
}
*/

void MainFrame::Oncb_engdefault(wxCommandEvent& event)
{
    if(cb_engdefault->GetValue()) {
        writejuliusconf("lvauto");
        sp_engthreshold->Enable(0);
        //s_englevel->Enable(0);
        sp_engzero->Enable(0);
		//s_englevel->SetValue(2000);
		sp_engzero->SetValue(60);
		sp_engthreshold->SetValue(2000);
    } else {
        writejuliusconf("lv");
        writejuliusconf("zc");
        sp_engthreshold->Enable(1);
        //s_englevel->Enable(1);
        sp_engzero->Enable(1);
    }
}

void MainFrame::Onsp_engthreshold(wxSpinEvent& event)
{
    writejuliusconf("lv");
    //s_englevel->SetValue(event.GetInt());
}

void MainFrame::Onsp_engzero(wxSpinEvent& event)
{
    writejuliusconf("zc");
}

/*
void MainFrame::Oncb_engnostrip(wxCommandEvent& event)
{
    writejuliusconf("nostrip");
}
*/


void  MainFrame::Onb_spectrum( wxCommandEvent& event )
{
	calculatespectrum();
}

void MainFrame::calculatespectrum()
{
	wxString cp;
	wxArrayString output, errors;
	int code = wxExecute("which kiku_mkss", output, errors);
	if ( code != -1 )
	{
		if(!output.IsEmpty()) {
			cp = output[0];
		}
	}
	if(cp == "") {
		wxMessageBox("cannot find kiku_mkss.");
	} else {
		wxMessageBox("Will record your normal environment noise for 3 seconds, do not speak and keep the children calm!\n\nPress ok when you're ready.");
		wxArrayString outputic, errorsic;
		wxExecute("kiku_mkss -zmeanframe "+GetCurrentWorkingDirectory()+"/language/mkss", outputic, errorsic);
		writejuliusconf("ssload");		
		if(m_Julius && juliusisready) {
			juliusgentlyexit();
			startjuliusthread();
		}
	}
}

void MainFrame::Oncb_engzmean(wxCommandEvent& event)
{
    writejuliusconf("zmean");
}

void MainFrame::Onc_enggprune(wxCommandEvent& event)
{
    writejuliusconf("gprune");
}

void MainFrame::Onc_engiwcd1(wxCommandEvent& event)
{
    if(c_engiwcd1->GetStringSelection() == "best") {
        sp_engiwcd1->Enable(1);
    } else {
        sp_engiwcd1->Enable(0);
    }
    writejuliusconf("iwcd");
}

void MainFrame::Onsp_engiwcd1(wxSpinEvent& event)
{
    writejuliusconf("iwcdbest");
}

void MainFrame::Onsp_engtmix(wxSpinEvent& event)
{
    writejuliusconf("tmix");
}

void MainFrame::Onsp_engbeam(wxSpinEvent& event)
{
    writejuliusconf("beam");
}

void MainFrame::Oncb_beammax(wxCommandEvent& event)
{
	if(cb_beammax->GetValue()) {
		sp_engbeam->Enable(0);
		writejuliusconf("beammax");
	} else {
		sp_engbeam->Enable(1);
		sp_engbeam->SetValue(14000);
		writejuliusconf("beam");
	}
}

void MainFrame::Ontc_engpenalty(wxCommandEvent& event)
{
    writejuliusconf("penalty");
}

// restart julius
void MainFrame::Onb_restartjulius( wxCommandEvent& event ) {
	p_engine->Enable(0);
	juliusgentlyexit();
	startjuliusthread();
	p_engine->Enable(1);
}

////////////////////////////////////////////////////////////////////////////////
// JULIUS CALLBACK
////////////////////////////////////////////////////////////////////////////////
void MainFrame::onJuliusPronun(wxCommandEvent& event)
{
	// autopause sp
	if(event.GetString() == "sp") {
		if(cb_apsp->GetValue()) {
            autopause();
        }
    }
	// visual feedback 
	if(event.GetString() != "silB" && event.GetString() != "silE" && event.GetString() != "sp" && event.GetString() != "sil") {
        if(listening) {
			tcro_pronun->AppendText(event.GetString());
		}
    }
}

void MainFrame::onJuliusSentence(wxCommandEvent& event)
{
	wxString checktype;
	bool process = true;
	
	// do not autopause if listening stop
	if(listening) {
		// silence check
		if(event.GetString() == "") {
			tcro_word->SetDefaultStyle(wxTextAttr(*wxRED));
			// autopause based on SP
			if(cb_apsp->GetValue()) {
				autopause();
			}
			process = false;
		}

		// score threshold check
		tc_scorethres->GetValue().ToDouble(&threshold);
		if(score < threshold) {
			tcro_word->SetDefaultStyle(wxTextAttr(*wxRED));
			// autopause based on score
			if(cb_apscore->GetValue()) {
				autopause();
			}
			process = false;
		}
			
		// time duration check
		if(duration < sp_minlength->GetValue() || duration > sp_maxlength->GetValue()) {
			tcro_word->SetDefaultStyle(wxTextAttr(*wxRED));
			// autopause based on score
			if(cb_aptime->GetValue()) {
				autopause();
			}
			process = false;
		}
	}
	
	// ok process the word
	if(process) {
		
		tcro_word->SetDefaultStyle(wxTextAttr(*wxBLACK));
		
		// this word is a trigger
		if(actionwaiting) {
			int pos = trigger.Index(event.GetString().Upper());
			// if case that no application using this word
			if(pos != wxNOT_FOUND) {
				checktype = type.Item(pos);
			}
			// for the tb icon
			searchandexecute(event.GetString().Upper());
		} else {
			// exception first time test (give => donation)
			if(b_languagedownload->GetLabel() == "Download") {
				b_languagedownload->SetLabel("Downloaded");
				if(c_language->GetStringSelection() == "English 14k [VoxForge]") {
					if(event.GetString().Upper() == "GIVE") {
						wxLaunchDefaultBrowser("http://www.workinprogress.ca/kiku/donation/");
						calculatespectrum();
						html_language->LoadPage("http://www.workinprogress.ca/KIKU/help/language_v2c.html");
					}
				} else if(c_language->GetStringSelection() == "Japanese 20k [Julius]" || c_language->GetStringSelection() == "Japanese 60k [Julius]") {
					// kifu = donation
					if(event.GetString().Upper() == "寄付") {
						wxLaunchDefaultBrowser("http://www.workinprogress.ca/kiku/donation/");
						calculatespectrum();
						html_language->LoadPage("http://www.workinprogress.ca/KIKU/help/language_v2c.html");
					}
				} else if(c_language->GetStringSelection() == "German 370k [VoxForge]") {
					if(event.GetString().Upper() == "GEBEN") {
						wxLaunchDefaultBrowser("http://www.workinprogress.ca/kiku/donation/");
						calculatespectrum();
						html_language->LoadPage("http://www.workinprogress.ca/KIKU/help/language_v2c.html");
					}
				} else if(c_language->GetStringSelection() == "Portuguese 65k [Fala Brasil]") {
					if(event.GetString().Upper() == "DAR") {
						wxLaunchDefaultBrowser("http://www.workinprogress.ca/kiku/donation/");
						calculatespectrum();
						html_language->LoadPage("http://www.workinprogress.ca/KIKU/help/language_v2c.html");
					}
				}
				
			}			
			// search word in pretrigger
			triggering = pretrigger.Index(event.GetString().Upper());
			if(triggering != wxNOT_FOUND) {
				checktype = type.Item(triggering);
				// notification pretrig enable
				if(cb_notpretrig->GetValue()) {
					Eye(event.GetString().Upper());
				}
				actionwaiting = true;
				actionwaitingpretrigger = event.GetString().Upper();
				
				reseticonm_timer->Start(PRETRIGTIME);
				if(listening) {
					sb->SetStatusText("Waiting for action word", 2);
				}
			} else {
				// this word cannot be directly said (needs a pretrigger)
				int pos = trigger.Index(event.GetString().Upper());
				// if case that no application using this word
				if(pos != wxNOT_FOUND) {
					checktype = type.Item(pos);
					if(pretrigger.Item(pos) == "") {
						// for the tb icon
						recognized = true;
						reseticonm_timer->Start(1000);
						searchandexecute(event.GetString().Upper());
					} else {
						needpretrig = true;
						reseticonm_timer->Start(1000);
					}
				}
			}
		}
	} else {
		// last sentence was unknown (reflect in the taskbar icon - using timer)
		if(!actionwaiting) {
			unknown = true;
			reseticonm_timer->Start(1000);
		}
	}
	if(listening || checktype == "kiku") {
		// visual feedback
		wxString vf;
		vf = event.GetString() == "" || event.GetString() == "、" ? "SP" : event.GetString();
		tcro_word->AppendText(vf);
		tcro_word->AppendText("\n");
		
		if(!listening && checktype == "kiku") {
			tcro_score->AppendText("\n");
			tcro_pronun->AppendText("\n");
		}
	}
	
	// liblo - send recognition result via open sound control
	if(cb_oscrecognition->GetValue()) {
		lo_bundle osc_bundle = lo_bundle_new(LO_TT_IMMEDIATE);
		lo_message msg = lo_message_new();
		lo_message_add_int32(msg, duration);
		lo_message_add_float(msg, threshold);
		lo_message_add_string(msg, event.GetString());
		lo_bundle_add_message(osc_bundle, "/kiku", msg);
		if(lo_send_bundle(osc, osc_bundle) == -1) {
			wxMessageBox(wxString::Format("Problem with Open Sound Control:\n%s", lo_address_errstr(osc)));
		}
		lo_message_free(msg);
		lo_bundle_free(osc_bundle);
	}

}


void MainFrame::onJuliusScore(wxCommandEvent& event)
{
	if(listening) {
		tcro_score->AppendText(event.GetString());
		tcro_score->AppendText("\n");
		event.GetString().ToDouble(&score);
	}
}

void MainFrame::onJuliusReady(wxCommandEvent& event)
{
	//juliusisready = true;
	if(!paused && juliusisready) {
		if(event.GetString() == "Listening...") {
			icontb.CopyFromBitmap( *iconpng[6] );
			if (!m_taskBarIcon->SetIcon( icontb )) {
				wxMessageBox(wxT("Could not set icon."));
			}
		} else {
			
			if(actionwaiting) { // pre-trig
				icontb.CopyFromBitmap( *iconpng[3] );
				if (!m_taskBarIcon->SetIcon( icontb )) {
					wxMessageBox(wxT("Could not set icon."));
				}
			} else if(recognized) {
				icontb.CopyFromBitmap( *iconpng[7] ); // last sentence recognized
				if (!m_taskBarIcon->SetIcon( icontb )) {
					wxMessageBox(wxT("Could not set icon."));
				}
				recognized = false;
			} else if(unknown) { // last sentence was unknown
				icontb.CopyFromBitmap( *iconpng[4] );
				if (!m_taskBarIcon->SetIcon( icontb )) {
					wxMessageBox(wxT("Could not set icon."));
				}
				unknown = false;
			} else if(needpretrig) { // last sentence need a pretrig
				icontb.CopyFromBitmap( *iconpng[8] );
				if (!m_taskBarIcon->SetIcon( icontb )) {
					wxMessageBox(wxT("Could not set icon."));
				}
				needpretrig = false;
			} else {
				sb->SetStatusText("", 2);
				if(webupdateicon) {
					icontb.CopyFromBitmap( *iconpng[1] );
					if (!m_taskBarIcon->SetIcon( icontb )) {
						wxMessageBox(wxT("Could not set icon."));
					}
				} else {
					icontb.CopyFromBitmap( *iconpng[0] );
					if (!m_taskBarIcon->SetIcon( icontb )) {
						wxMessageBox(wxT("Could not set icon."));
					}
				}
			}
		}
		sb->SetStatusText(event.GetString());
	}
}

void MainFrame::onJuliusWatch(wxCommandEvent& event)
{
	// for time check
	duration = event.GetInt();		
    sb->SetStatusText("Duration: "+wxString::Format("%i", event.GetInt())+" ms", 1);
}

/*
void MainFrame::onJuliusLevelMeter(wxCommandEvent& event)
{
	g_englevel->SetValue(event.GetInt());
	//autounpause
    if(cb_pause->GetValue()) {
        if(cb_aptime->GetValue() || cb_apscore->GetValue() || cb_apsp->GetValue()) {
            if(event.GetInt() < sp_aupthreshold->GetValue() && !aup_timer_started) {
                aup_timer_started = true;
                aup_timer.Start();
            } else if(event.GetInt() < sp_aupthreshold->GetValue() && ceil(aup_timer.Time() / 1000) > sp_aupsec->GetValue()) {
				// user clicked on pause
				if(!aup_userpause) {
					cb_pause->SetValue(0);
					if(webupdateicon) {
						icontb.CopyFromBitmap( *iconpng[1] );
						if (!m_taskBarIcon->SetIcon( icontb )) {
							wxMessageBox(wxT("Could not set icon."));
						}
					} else {
						icontb.CopyFromBitmap( *iconpng[0] );
						if (!m_taskBarIcon->SetIcon( icontb )) {
							wxMessageBox(wxT("Could not set icon."));
						}
					}
					m_Julius->resume_recognition();
					sb->SetStatusText("You can now speak.");
					paused = false;
				}
            } else if(event.GetInt() > sp_aupthreshold->GetValue()) {
                //restart
                aup_timer.Start();
            }
            aup_timer_ispaused = false;

        }
    } else {
        if(!aup_timer_ispaused) {
            aup_timer.Pause();
        }
    }
}
*/
////////////////////////////////////////////////////////////////////////////////
// PAUSE
////////////////////////////////////////////////////////////////////////////////
void MainFrame::Oncb_pause(wxCommandEvent& event)
{
    pauser(event.GetInt());
}

void MainFrame::pauser(bool state)
{
	
    if(state && juliusisready) {
		aup_userpause = true;
		cb_pause->SetValue(1);
        icontb.CopyFromBitmap( *iconpng[2] );
		if (!m_taskBarIcon->SetIcon( icontb )) {
			wxMessageBox(wxT("Could not set icon."));
		}
		if(listening) {
			m_Julius->pause_recognition();
		}
        paused = true;
		sb->SetStatusText("Paused.");
    } else {
		cb_pause->SetValue(0);
		listening = true;
        m_Julius->resume_recognition();
        paused = false;
		sb->SetStatusText("You can now speak.");
		if(webupdateicon) {
			icontb.CopyFromBitmap( *iconpng[1] );
			if (!m_taskBarIcon->SetIcon( icontb )) {
				wxMessageBox(wxT("Could not set icon."));
			}
		} else {
			icontb.CopyFromBitmap( *iconpng[0] );
			if (!m_taskBarIcon->SetIcon( icontb )) {
				wxMessageBox(wxT("Could not set icon."));
			}
		}
    }	
	sb->SetStatusText("", 2);
	
}

////////////////////////////////////////////////////////////////////////////////
// PREFERENCE
////////////////////////////////////////////////////////////////////////////////
void MainFrame::readpreference()
{
	
    wxFileInputStream inputpref(GetCurrentWorkingDirectory()+"/preference.conf");
    wxJSONValue  rootpref;
    wxJSONReader readerpref;

    int numErrorspref = readerpref.Parse( inputpref, &rootpref );
    if ( numErrorspref > 0 )  {
        wxMessageBox("ERROR: the JSON preference.conf document is not well-formed");
    }

	// language
	if(rootpref["language"].AsString() == "en") {
		st_language_select->SetLabel("English 14k [VoxForge]");
		language = "en";
		c_language->Show(0);
		b_languagedownload->SetLabel("Update");
	} else if(rootpref["language"].AsString() == "jp") {
		st_language_select->SetLabel("Japanese 20k [Julius]");
		language = "jp";
		c_language->Show(0);
		b_languagedownload->Show(0);
	} else if(rootpref["language"].AsString() == "jp60k") {
		st_language_select->SetLabel("Japanese 60k [Julius]");
		language = "jp60k";
		c_language->Show(0);
		b_languagedownload->Show(0);
	} else if(rootpref["language"].AsString() == "german") {
		st_language_select->SetLabel("German 370k [VoxForge]");
		language = "german";
		c_language->Show(0);
		b_languagedownload->Show(0);
	} else if(rootpref["language"].AsString() == "portuguese") {
		st_language_select->SetLabel("Portuguese 65k [Fala Brasil]");
		language = "portuguese";
		c_language->Show(0);
		b_languagedownload->Show(0);
	}
	if(rootpref["threshold"].IsInt()) {
		if(rootpref["threshold"].AsInt() <= 0) {
			tc_scorethres->ChangeValue("0.000000");
		} else if(rootpref["threshold"].AsInt() >= 1) {
			tc_scorethres->ChangeValue("1.000000");
		}
	} else {
		tc_scorethres->ChangeValue(wxString::Format("%f",rootpref["threshold"].AsDouble()));
	}
    
    sp_minlength->SetValue(rootpref["minimum"].AsInt());
    sp_maxlength->SetValue(rootpref["maximum"].AsInt());

    c_notstyle->SetStringSelection(rootpref["notificationstyle"].AsString());
    sp_notdelay->SetValue(rootpref["notificationdelay"].AsInt());
    cb_notpretrig->SetValue(rootpref["notificationtrig"].AsBool());

	cb_dict->SetValue(rootpref["dictionary"].AsBool());
	
    sp_apmistake->SetValue(rootpref["autopause_mistake"].AsInt());
    sp_apsec->SetValue(rootpref["autopause_sec"].AsInt());
    cb_apscore->SetValue(rootpref["autopause_score"].AsBool());
    cb_aptime->SetValue(rootpref["autopause_time"].AsBool());
    cb_apsp->SetValue(rootpref["autopause_sp"].AsBool());
    if(!cb_apsp->GetValue() && !cb_aptime->GetValue() && !cb_apscore->GetValue()) {
        sp_apmistake->Enable(0);
        sp_apsec->Enable(0);
        //sp_aupthreshold->Enable(0);
        sp_aupsec->Enable(0);
    }
    //sp_aupthreshold->SetValue(rootpref["autounpause_threshold"].AsInt());
    sp_aupsec->SetValue(rootpref["autounpause_sec"].AsInt());

    if(rootpref["v2c_loading"].AsInt() == 0) {
        rb_v2cmethod->SetSelection(0);
        cb_v2cmonitor->Enable(0);
        cb_v2clauncher->Enable(0);
    } else if(rootpref["v2c_loading"].AsInt() == 1) {
        rb_v2cmethod->SetSelection(1);
        cb_v2cmonitor->Enable(1);
        cb_v2clauncher->Enable(1);
        cb_v2cmonitor->SetValue(rootpref["v2c_monitor"].AsBool());
        cb_v2clauncher->SetValue(rootpref["v2c_apps"].AsBool());
    }

    if(c_notstyle->GetStringSelection() == "None") {
        sp_notdelay->Enable(0);
        cb_notpretrig->Enable(0);
        sp_notdelay->Enable(0);
    } else {
        sp_notdelay->Enable(1);
        cb_notpretrig->Enable(1);
        sp_notdelay->Enable(1);
    }
	
	// libpd
	c_filter->SetStringSelection(rootpref["libpd_filter"].AsString());
	libpd_float("filter", c_filter->GetCurrentSelection());
	
	s_volume->SetValue(rootpref["libpd_volume"].AsInt());
	st_volume->SetLabel(wxString::Format("%i%%", rootpref["libpd_volume"].AsInt()));
	libpd_float("volume", rootpref["libpd_volume"].AsInt());
	
	s_lp->SetValue(rootpref["libpd_lp"].AsInt());
	st_lp->SetLabel(wxString::Format("%i hertz", rootpref["libpd_lp"].AsInt()));
	libpd_float("lp", rootpref["libpd_lp"].AsInt());
	
	s_hp->SetValue(rootpref["libpd_hp"].AsInt());
	st_hp->SetLabel(wxString::Format("%i hertz", rootpref["libpd_hp"].AsInt()));
	libpd_float("hp", rootpref["libpd_hp"].AsInt());
	
	if(c_filter->GetStringSelection() == "None") {
		s_lp->Enable(0);
		s_hp->Enable(0);
	}
	
	// liblo
	// update v1 to v2
	if(rootpref["osc_enable"].IsNull()) {
		cb_oscenable->SetValue(0);
		tc_oschost->ChangeValue("localhost");
		sp_oscport->SetValue(9997);
		c_oscprotocol->SetStringSelection("UDP");
		cb_oscrecognition->SetValue(0);
		writepreference();
	} else {
		cb_oscenable->SetValue(rootpref["osc_enable"].AsBool());
		tc_oschost->ChangeValue(rootpref["osc_host"].AsString());
		sp_oscport->SetValue(rootpref["osc_port"].AsInt());
		c_oscprotocol->SetStringSelection(rootpref["osc_protocol"].AsString());
		cb_oscrecognition->SetValue(rootpref["osc_recognition"].AsBool());
	}
	
	if(!cb_oscenable->GetValue()) {
		sp_oscport->Enable(0);
		c_oscprotocol->Enable(0);
		tc_oschost->Enable(0);
		cb_oscrecognition->Enable(0);
	}
}

void MainFrame::writepreference()
{
	// gui logic
	
	// ap & aup
	if(!cb_apscore->GetValue() && !cb_aptime->GetValue() && !cb_apsp->GetValue()) {
		sp_apmistake->Enable(0);
		sp_apsec->Enable(0);
		sp_aupsec->Enable(0);
		//sp_aupthreshold->Enable(0);
	} else {
		sp_apmistake->Enable(1);
		sp_apsec->Enable(1);
		sp_aupsec->Enable(1);
		//sp_aupthreshold->Enable(1);
	}

	// limit logic
	if(sp_minlength->GetValue() >= sp_maxlength->GetValue()) {
		sp_minlength->SetValue(sp_maxlength->GetValue() - 1);
	}
	if(sp_maxlength->GetValue() <= sp_minlength->GetValue()) {
		sp_maxlength->SetValue(sp_maxlength->GetValue() + 1);
	}
	
	// actual file save
    wxJSONValue preference;
    preference.AddComment( "// preferences - do not edit by hand", wxJSONVALUE_COMMENT_BEFORE );
	
	// language
	if(language == "") {
		preference["language"] = _T("none");
	} else {
		preference["language"] = language;
	}
	
	double threshold;
    tc_scorethres->GetValue().ToDouble(&threshold);
    preference["threshold"] = threshold;
    preference["minimum"] = sp_minlength->GetValue();
    preference["maximum"] = sp_maxlength->GetValue();
	
	

	preference["dictionary"] = cb_dict->GetValue();
	
    preference["notificationstyle"] = c_notstyle->GetStringSelection();
    preference["notificationdelay"] = sp_notdelay->GetValue();
    preference["notificationtrig"] = cb_notpretrig->GetValue();

    preference["autopause_mistake"] = sp_apmistake->GetValue();
    preference["autopause_sec"] = sp_apsec->GetValue();
    preference["autopause_score"] = cb_apscore->GetValue();
    preference["autopause_time"] = cb_aptime->GetValue();
    preference["autopause_sp"] = cb_apsp->GetValue();
    //preference["autounpause_threshold"] = sp_aupthreshold->GetValue();
    preference["autounpause_sec"] = sp_aupsec->GetValue();
	
    int v2copt;
    if(rb_v2cmethod->GetSelection() == 0) {
        v2copt = 0;
    } else {
        v2copt = 1;
    }
    preference["v2c_loading"] = v2copt;
    preference["v2c_monitor"] = cb_v2cmonitor->GetValue();
    preference["v2c_apps"] = cb_v2clauncher->GetValue();
	
	// libpd
	preference["libpd_volume"] = s_volume->GetValue();
	preference["libpd_filter"] = c_filter->GetStringSelection();
	preference["libpd_lp"] = s_lp->GetValue();
	preference["libpd_hp"] = s_hp->GetValue();
	
	// liblo
	preference["osc_enable"] = cb_oscenable->GetValue();
	preference["osc_host"] = tc_oschost->GetValue();
	preference["osc_port"] = sp_oscport->GetValue();
	preference["osc_protocol"] = c_oscprotocol->GetStringSelection();
	preference["osc_recognition"] = cb_oscrecognition->GetValue();
	
    wxJSONWriter writer( wxJSONWRITER_STYLED | wxJSONWRITER_WRITE_COMMENTS );
    wxString  jsonText;
    writer.Write( preference, jsonText );
    wxFile myFile(GetCurrentWorkingDirectory()+"/preference.conf", wxFile::write);
    myFile.Write(jsonText);
    myFile.Close();
}

void MainFrame::createpreference()
{
	wxJSONValue preference;
    preference.AddComment( "// preferences - do not edit by hand", wxJSONVALUE_COMMENT_BEFORE );
	preference["language"] = _T("none");
    preference["threshold"] = 0.845000;
    preference["minimum"] = 300;
    preference["maximum"] = 2000;
    preference["notificationstyle"] = _T("None");
    preference["notificationdelay"] = 1;
    preference["notificationtrig"] = false;
    preference["autopause_mistake"] = 6;
    preference["autopause_sec"] = 10;
    preference["autopause_score"] = true;
    preference["autopause_time"] = true;
    preference["autopause_sp"] = true;
    preference["autounpause_threshold"] = 1999;
    preference["autounpause_sec"] = 10;
	preference["dictionary"] = true;
    preference["v2c_loading"] = 1;
    preference["v2c_monitor"] = true;
    preference["v2c_apps"] = true;
	preference["libpd_filter"] = _T("2-order (butterworth)");
    preference["libpd_volume"] = 100;
    preference["libpd_lp"] = 11500;
    preference["libpd_hp"] = 200;
	preference["osc_enable"] = false;
	preference["osc_host"] = _T("localhost");
	preference["osc_port"] = 9997;
	preference["osc_protocol"] = _T("UDP");
	preference["osc_recognition"] = false;
	
    wxJSONWriter writer( wxJSONWRITER_STYLED | wxJSONWRITER_WRITE_COMMENTS );
    wxString  jsonText;
    writer.Write( preference, jsonText );
    wxFile myFile(GetCurrentWorkingDirectory()+"/preference.conf", wxFile::write);
    myFile.Write(jsonText);
    myFile.Close();
}

// update pref
void MainFrame::Onm_prefupdate( wxCommandEvent& event ) { 
	writepreference();
}

void MainFrame::Onc_notification(wxCommandEvent& event)
{
	if(c_notstyle->GetStringSelection() != "None") {
		if(c_notstyle->GetStringSelection() == "Notify") {
			wxMessageBox("If you are using Notify OSD (default on Ubuntu) the delay will not work. Hopefully this bug will be fix in a near future.");
			sp_notdelay->Enable(1);
			cb_notpretrig->Enable(1);
		} else if(c_notstyle->GetStringSelection() == "XOSD") {
			sp_notdelay->Enable(1);
			cb_notpretrig->Enable(1);
		}
		sp_notdelay->Enable(1);
		cb_notpretrig->Enable(1);
	} else {
		sp_notdelay->Enable(0);
		cb_notpretrig->Enable(0);
	}
	writepreference();
}

////////////////////////////////////////////////////////////////////////////////
// TIMERS
////////////////////////////////////////////////////////////////////////////////
void MainFrame::OnResetIconTimer(wxTimerEvent& event)
{
	if(!paused) {
		if(webupdateicon) {
			icontb.CopyFromBitmap( *iconpng[1] );
			if (!m_taskBarIcon->SetIcon( icontb )) {
				wxMessageBox(wxT("Could not set icon."));
			}
		} else {
			icontb.CopyFromBitmap( *iconpng[0] );
			if (!m_taskBarIcon->SetIcon( icontb )) {
				wxMessageBox(wxT("Could not set icon."));
			}
		}
		reseticonm_timer->Stop();
		
		// be sure it's an actionwaiting call
		if(!recognized && !unknown) {
			actionwaiting = false;
			sb->SetStatusText("", 2);
		}
	}
}

void MainFrame::OnUnpauseTimer(wxTimerEvent& event)
{
	pauser(false);
	unpausem_timer->Stop();
}

////////////////////////////////////////////////////////////////////////////////
// AUTOPAUSE
////////////////////////////////////////////////////////////////////////////////
void MainFrame::autopause()
{
    nbmistake++;
    if(nbmistake == 1) {
        //start timer
        ap_timer.Start();
    }
    if(ceil(ap_timer.Time() / 1000) > sp_apsec->GetValue()) {
        nbmistake = 0;
    } else if(nbmistake == sp_apmistake->GetValue()) {
		pauser(1);
		aup_userpause = false;
		nbmistake = 0;
		//restart unpause timer
		//aup_timer.Start();
		unpausem_timer->Start(sp_aupsec->GetValue() * 1000);
	}
    
}

////////////////////////////////////////////////////////////////////////////////
// ACTION
////////////////////////////////////////////////////////////////////////////////
void MainFrame::searchandexecute(wxString word)
{
    long pid;
    actionning = trigger.Index(word);

    // found this word in trigger
    if(actionning != wxNOT_FOUND) {
		
		bool go = false;
		
		// check if this trigger is for the actual pretrigger
		if(actionwaiting) {

			if(actionwaitingpretrigger == pretrigger.Item(actionning)) {
				go = true;
			}
		} else {
			go = true;
		}
		
		//if(pretrigger.Item(actionning) == "" || actionwaiting) {
		if(go) {
			pid = Hand(type.Item(actionning), command.Item(actionning));
			// notification
			Eye(noti.Item(actionning));
			
			// v2clauncher mode
			if(v2clauncher == true) {
					
					// load the corresponding .v2c
					if(v2c.Item(actionning) == "launcher") {
							#ifdef DEBUG
								wxPuts("++++++++++++++++++++++++++++");
								wxPuts("Launcher...");
								wxPuts("File: "+GetCurrentWorkingDirectory() + "/v2c/" + process.Item(actionning) + ".v2a");
								wxPuts(wxString::Format("PID: %li", pid));
								wxPuts("++++++++++++++++++++++++++++");
							#endif
							
							v2cloading(GetCurrentWorkingDirectory() + "/v2c/" + process.Item(actionning) + ".v2a", pid);
							pspnameid.Add(process.Item(actionning));
					}
					
			} else {
				recognized = true;
				reseticonm_timer->Start(1000);
				sb->SetStatusText("", 2);
			}
			actionwaiting = false;
		}
    }
}

void MainFrame::Eye(wxString txt)
{
	if(txt != "") {
		if(c_notstyle->GetStringSelection() == "Built-in") {
			wxNotificationMessage hey;
			hey.SetMessage(txt);
			hey.Show(sp_notdelay->GetValue());
		} else if(c_notstyle->GetStringSelection() == "Notify") {
			// add an exception
			#if LIBNOTIFYVER == 4
				nn = notify_notification_new("kiku", txt, NULL);
			#else
				nn = notify_notification_new("kiku", txt, NULL, NULL);
			#endif
			notify_notification_set_timeout(nn, sp_notdelay->GetValue());
			if (!notify_notification_show(nn, NULL))
			{
				wxMessageBox("Please report this problem to: kiku@11h11.com");
			}
			g_object_unref(G_OBJECT(nn));
			/*
			wxString delay;
			delay << sp_notdelay->GetValue();
			int code = wxExecute("notify-send -t " + delay + " \"" + txt + "\"", output, errors);
			if ( code != -1 )
			{
				if(!output.IsEmpty()) {
					cp = output[0];
				}
			}
			*/
		} else if(c_notstyle->GetStringSelection() == "XOSD") {
			
			char cstring[4024];
			strncpy(cstring, (const char*)txt.mb_str(wxConvUTF8), 4023);
			xosd_display(osd, 0, XOSD_string, cstring);
		}
	}
}

long MainFrame::Hand(wxString type, wxString cmd)
{
	int xdotoolwindowid = xdotoolwindow;

	if(type == "shell" && listening) { // launcher
		#ifdef DEBUG
			wxPuts(type + " : " + cmd);
		#endif
		proc = new Process(this, cmd);
		m_pidLast = wxExecute(cmd, wxEXEC_ASYNC, proc);
		if ( !m_pidLast )
		{
			wxLogError( _T("Execution of '%s' failed."), cmd.c_str() );
			delete proc;
		}
		return m_pidLast;
	} else if(type == "xdotool" && listening) { // xdotool	
		// tokenize |
		wxArrayString acmd = wxStringTokenize(cmd, "|");
		for (size_t i=0; i < acmd.GetCount(); i++) {
			if(acmd[i].Trim().Trim(false) != "") {
				#ifdef DEBUG
					wxPuts(type + ": " + acmd[i].Trim().Trim(false));
				#endif
				// get the function to call (key, type, ...)
				wxArrayString xcmd = wxStringTokenize(acmd[i].Trim().Trim(false), " ");
				if(xcmd[0] == "activate") {
					Window *list;
					int nwindows;
					int i;
					xdo_search_t search;
					memset(&search, 0, sizeof(xdo_search_t));
					search.max_depth = -1;
					search.searchmask |= (SEARCH_NAME | SEARCH_CLASS | SEARCH_CLASSNAME);
					search.winname = xcmd[1];
					search.winclass = xcmd[1];
					search.winclassname = xcmd[1];
					xdo_window_search(xdo, &search, &list, &nwindows);
					
					if (nwindows) {
						xdo_window_activate(xdo, list[0]);
						xdo_window_wait_for_active(xdo, list[0], 1);
						xdotoolwindowid = list[0];
					}
					
					for (i = 0; i < nwindows; i++) {
						//xdo_window_activate(xdo, list[i]);
						//xdo_window_wait_for_active(xdo, list[i], 1);
						#ifdef DEBUG
							wxPuts(wxString::Format("found window: %ld", list[i]));
						#endif
					}
					if (nwindows == 0) {
						#ifdef DEBUG
							wxPuts("no window found");
						#endif
					}
					if (list != NULL) {
						free(list);
					}
				} else if(xcmd[0] == "sleep") {
					double duration_usec;
					duration_usec = atof(xcmd[1]) * (1000000);
					usleep(duration_usec);	
				} else if(xcmd[0] == "key") {
						int usethiswindow;
						if(xdotoolwindowid) {
							usethiswindow = xdotoolwindowid;
						} else {
							usethiswindow = xdotoolwindow;
						}
						//xdo_active_mods_t *active_mods = NULL;
						//active_mods = xdo_get_active_modifiers(xdo);
						//xdo_clear_active_modifiers(xdo, usethiswindow, active_mods);
						xdo_keysequence(xdo, usethiswindow, (const_cast<char*>((const char*)acmd[i].Trim().Trim(false).Mid(4).mb_str())), 6000);
						//xdo_set_active_modifiers(xdo, usethiswindow, active_mods);
						//xdo_free_active_modifiers(active_mods);
				} else if(xcmd[0] == "keydown") {
						int usethiswindow;
						if(xdotoolwindowid) {
							usethiswindow = xdotoolwindowid;
						} else {
							usethiswindow = xdotoolwindow;
						}
						//xdo_active_mods_t *active_mods = NULL;
						//active_mods = xdo_get_active_modifiers(xdo);
						//xdo_clear_active_modifiers(xdo, usethiswindow, active_mods);
						xdo_keysequence_down(xdo, usethiswindow, (const_cast<char*>((const char*)acmd[i].Trim().Trim(false).Mid(8).mb_str())), 6000);
						//xdo_set_active_modifiers(xdo, usethiswindow, active_mods);
						//xdo_free_active_modifiers(active_mods);
				} else if(xcmd[0] == "keyup") {					
						int usethiswindow;
						if(xdotoolwindowid) {
							usethiswindow = xdotoolwindowid;
						} else {
							usethiswindow = xdotoolwindow;
						}
						//xdo_active_mods_t *active_mods = NULL;
						//active_mods = xdo_get_active_modifiers(xdo);
						//xdo_clear_active_modifiers(xdo, usethiswindow, active_mods);
						xdo_keysequence_up(xdo, usethiswindow, (const_cast<char*>((const char*)acmd[i].Trim().Trim(false).Mid(6).mb_str())), 6000);
						//xdo_set_active_modifiers(xdo, usethiswindow, active_mods);
						//xdo_free_active_modifiers(active_mods);
				} else if(xcmd[0] == "type") {
					xdo_type(xdo, xdotoolwindow, (const_cast<char*>((const char*)acmd[i].Trim().Trim(false).Mid(5).mb_str())), xdotooldelay);
				} else if(xcmd[0] == "mousemove_relative") {
					xdo_mousemove_relative (xdo, wxAtoi(xcmd[1]), wxAtoi(xcmd[2]));
				} else if(xcmd[0] == "mousemove") {
					xdo_mousemove (xdo, wxAtoi(xcmd[1]), wxAtoi(xcmd[2]), xdotoolwindow);
				} else if(xcmd[0] == "click") {
					int button = 1;
					if(xcmd.GetCount() > 1) {
						if(xcmd[1] == "middle") {
							button = 2;
						} else if(xcmd[1] == "right") {
							button = 3;
						}
					}
					xdo_click(xdo, xdotoolwindow, button);
				} else if(xcmd[0] == "mousedown") {
					int button = 1;
					if(xcmd.GetCount() > 1) {
						if(xcmd[1] == "middle") {
							button = 2;
						} else if(xcmd[1] == "right") {
							button = 3;
						}
					}
					xdo_mousedown (xdo, xdotoolwindow, button);
				} else if(xcmd[0] == "mouseup") {
					int button = 1;
					if(xcmd.GetCount() > 1) {
						if(xcmd[1] == "middle") {
							button = 2;
						} else if(xcmd[1] == "right") {
							button = 3;
						}
					}
					xdo_mouseup (xdo, xdotoolwindow, button);
				} else if(xcmd[0] == "term") {
					wxPuts(xcmd[1]);
					wxString cp;
					wxArrayString output, errors;
					int code = wxExecute(xcmd[1]);
					if ( code != -1 )
					{
						if(!output.IsEmpty()) {
							cp = output[0];
							wxPuts(cp);
						}
					}
				}
			}
		}
	} else if(type == "gnome" && listening) { // gnome
		// tokenize |
		wxArrayString acmd = wxStringTokenize(cmd, "|");
		wxString command;
		wxString defaultapp;
		if(acmd[0].Trim().Trim(false) != "") {
			command = acmd[0].Trim().Trim(false);
		} else {
			command = "";
		}
		if(acmd.GetCount() > 1) {
			if(acmd[1].Trim().Trim(false) != "") {
				defaultapp = acmd[1].Trim().Trim(false);
			} else {
				defaultapp = "";
			}
		} else {
			defaultapp = "";
		}
		gnome_cr(command, defaultapp);
		
	} else if(type == "kiku") { // kiku internal command
		if(cmd == "pause") {
			listening = false;
			pauser(true);
		} else if(cmd == "unpause") {
			pauser(false);
			sb->SetStatusText("You can now speak.");
		} else if(cmd == "activeword") {
			Dob_activeword();
		} else if(cmd == "dictation") {
			wxLaunchDefaultBrowser("http://www.workinprogress.ca/KIKU/dictation.php");
			listening = false;
			pauser(true);
		} else if(cmd == "quit") {
			reseticonm_timer->Stop();
			listening = false;
			pauser(true);
			OnQuit();
		}
	} else if(type == "open sound control") { // liblo
	
	
		if(!cb_oscenable->GetValue()) {
			
			wxMessageBox("Open Sound Control is not enabled (see Configuration tab)");
			
		} else {
			
			// tokenize (space)
			wxArrayString acmd = wxStringTokenize(cmd, " ");
			if(acmd.GetCount() == 1) {
				
				if (lo_send(osc, acmd[0].Trim().Trim(false), NULL) == -1) {
					wxMessageBox(wxString::Format("Problem with Open Sound Control:\n%s", lo_address_errstr(osc)));
				}
				
			} else if(acmd.GetCount() > 1) {
				
				
				lo_bundle osc_bundle = lo_bundle_new(LO_TT_IMMEDIATE);
				lo_message msg = lo_message_new();
					
				for (size_t i=1; i < acmd.GetCount(); i++) {
					
					// check for integer
					wxString isint(acmd[i].Trim().Trim(false));
					long valuei;
					// check for float
					wxString isfloat(acmd[i].Trim().Trim(false));
					double valuef;
					
					if(isint.ToLong(&valuei)) {
						lo_message_add_int32(msg, valuei);
					} else if(isfloat.ToDouble(&valuef)) {
						lo_message_add_float(msg, valuef);
					} else {
						if(acmd[i].Trim().Trim(false) == "TRUE") {
							lo_message_add_true(msg);
						} else if(acmd[i].Trim().Trim(false) == "FALSE") {
							lo_message_add_false(msg);
						} else {
							lo_message_add_string(msg, acmd[i].Trim().Trim(false));
						}
					}

				}
				
				lo_bundle_add_message(osc_bundle, acmd[0].Trim().Trim(false), msg);
				if(lo_send_bundle(osc, osc_bundle) == -1) {
					wxMessageBox(wxString::Format("Problem with Open Sound Control:\n%s", lo_address_errstr(osc)));
				}
				
				lo_message_free(msg);
				lo_bundle_free(osc_bundle);
				
			}
		}
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////////////
// MISC
////////////////////////////////////////////////////////////////////////////////
void MainFrame::OnLink(wxHtmlLinkEvent& event) {
	wxHtmlLinkInfo link;
	link = event.GetLinkInfo();
	wxLaunchDefaultBrowser(link.GetHref());
}

wxString MainFrame::GetCurrentWorkingDirectory()
{
    return stdpath.GetUserDataDir();
}

////////////////////////////////////////////////////////////////////////////////
// JULIUS THREAD
////////////////////////////////////////////////////////////////////////////////
JuliusThread::ExitCode JuliusThread::Entry()
{
	#ifdef DEBUG
		fprintf(stdout, "Start kiku\n");
	#endif
	
	// infinite loop
	m_pHandler->startjulius();

	return (wxThread::ExitCode)0; // success
}

JuliusThread::~JuliusThread()
{
	wxCriticalSectionLocker enter(m_pHandler->m_pThreadCS);
	m_pHandler->m_pThread = NULL;
}

////////////////////////////////////////////////////////////////////////////////
// TASKBAR
////////////////////////////////////////////////////////////////////////////////
enum {
    PU_EXIT,
	PU_APP,
	PU_SHORTCUT,
    PU_CHECKMARK,
	PU_ACTIVEWORD,
	PU_WEBSITE,
	PU_UPDATE
};

BEGIN_EVENT_TABLE(MainTaskBarIcon, wxTaskBarIcon)
    EVT_MENU(PU_CHECKMARK, MainTaskBarIcon::OnShowKiku)
    EVT_UPDATE_UI(PU_CHECKMARK,MainTaskBarIcon::OnMenuUICheckmark)
    EVT_TASKBAR_LEFT_DOWN(MainTaskBarIcon::OnLeftButtonDClick)
	EVT_MENU(PU_EXIT, MainTaskBarIcon::OnMenuExit)
	EVT_MENU(PU_APP, MainTaskBarIcon::OnMenuApp)
	EVT_MENU(PU_SHORTCUT, MainTaskBarIcon::OnMenuShortcut)
	EVT_MENU(PU_WEBSITE, MainTaskBarIcon::OnMenuWebsite)
	EVT_MENU(PU_ACTIVEWORD, MainTaskBarIcon::OnMenuActiveWord)
	EVT_MENU(PU_UPDATE, MainTaskBarIcon::OnMenuDownloadUpdate)
END_EVENT_TABLE()


MainTaskBarIcon::MainTaskBarIcon(MainFrame *handler)
{
	wxStandardPaths stdpath = wxStandardPaths::Get();
	
	m_pHandler = handler;
	if(!wxFileExists(stdpath.GetUserDataDir()+"/language/julius.conf")) {
		check = true;
	} else {
		check = false;
	}
}

void MainTaskBarIcon::OnShowKiku(wxCommandEvent& )
{
	if(check) {
		kiku->Hide();
	} else {
		kiku->Show();
	}

	check = !check;
}

void MainTaskBarIcon::OnMenuUICheckmark(wxUpdateUIEvent &event)
{
	event.Check( check );
}

void MainTaskBarIcon::OnLeftButtonDClick(wxTaskBarIconEvent&)
{
	if(m_pHandler->m_Julius && juliusisready) {
		m_pHandler->pauser(!paused);
	}
}

void MainTaskBarIcon::OnMenuExit(wxCommandEvent& )
{
	m_pHandler->OnQuit();
}

void MainTaskBarIcon::OnMenuWebsite(wxCommandEvent& )
{
	wxLaunchDefaultBrowser("http://www.workinprogress.ca/kiku/");
}

void MainTaskBarIcon::OnMenuDownloadUpdate(wxCommandEvent& )
{
	wxLaunchDefaultBrowser(updateurl);
	m_pHandler->OnQuit();
}

void MainTaskBarIcon::OnMenuApp(wxCommandEvent& )
{
	wxStandardPaths stdpath = wxStandardPaths::Get();
	
	if(!wxFileExists(stdpath.GetUserDataDir()+"/language/julius.conf")) {
		wxMessageBox("You need to install a language.");
	} else {
		m_pHandler->Dopb_v2capplication();
	}
}

void MainTaskBarIcon::OnMenuShortcut(wxCommandEvent& )
{
	wxStandardPaths stdpath = wxStandardPaths::Get();
	
	if(!wxFileExists(stdpath.GetUserDataDir()+"/language/julius.conf")) {
		wxMessageBox("You need to install a language.");
	} else {
		m_pHandler->Dopb_v2cshortcut();
	}
}

void MainTaskBarIcon::OnMenuActiveWord(wxCommandEvent& )
{
	wxStandardPaths stdpath = wxStandardPaths::Get();
	
	if(!wxFileExists(stdpath.GetUserDataDir()+"/language/julius.conf")) {
		wxMessageBox("You need to install a language.");
	} else {
		m_pHandler->Dob_activeword();
	}
}

wxMenu *MainTaskBarIcon::CreatePopupMenu()
{
    wxMenu *menu = new wxMenu;
    menu->Append(PU_CHECKMARK, "Show kiku", "", wxITEM_CHECK);
	menu->AppendSeparator();
	menu->Append(PU_APP, "Add an application");
	menu->Append(PU_SHORTCUT, "Add a shortcut");
	menu->Append(PU_ACTIVEWORD, "Active word");\
	menu->AppendSeparator();
	if(haveupdate) {
		menu->Append(PU_UPDATE, "Download update");
	}
	menu->Append(PU_WEBSITE, "Website");
    menu->Append(PU_EXIT, "Quit");
    return menu;
}