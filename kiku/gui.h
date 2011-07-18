///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  6 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/html/htmlwin.h>
#include <wx/notebook.h>
#include <wx/radiobox.h>
#include <wx/statline.h>
#include <wx/gauge.h>
#include <wx/slider.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxNotebook* m_nb;
		wxPanel* p_recognition;
		wxStaticText* m_staticText1;
		wxTextCtrl* tcro_word;
		wxStaticText* m_staticText11;
		wxTextCtrl* tcro_pronun;
		wxStaticText* m_staticText111;
		wxTextCtrl* tcro_score;
		wxCheckBox* cb_pause;
		wxStaticBitmap* bm_update;
		wxButton* b_update;
		
		wxStaticText* m_staticText8;
		wxTextCtrl* tc_scorethres;
		wxStaticText* m_staticText9;
		wxSpinCtrl* sp_minlength;
		wxStaticText* m_staticText10;
		wxSpinCtrl* sp_maxlength;
		wxButton* b_activeword;
		wxPanel* p_V2C;
		wxNotebook* m_nbv2c;
		wxPanel* p_v2capplication;
		wxButton* pb_v2capplication;
		wxStaticText* st_defined;
		wxChoice* pc_v2capplication;
		wxButton* pb_v2capplicationedit;
		wxHtmlWindow* html_v2capplication;
		wxPanel* p_v2cshortcut;
		wxButton* pb_v2cshortcut;
		wxStaticText* st_shortcutdefined;
		wxChoice* pc_v2cshortcut;
		wxButton* pb_v2cshortcutedit;
		wxHtmlWindow* html_v2cshortcut;
		wxPanel* p_v2cimport;
		wxStaticText* m_staticText33;
		wxChoice* pc_v2cimportapp;
		wxButton* b_v2cimportapp;
		wxStaticText* m_staticText34;
		wxChoice* pc_v2cimportshortcut;
		wxButton* b_v2cimportshortcut;
		wxHtmlWindow* html_import;
		wxPanel* p_configutation;
		wxStaticText* m_staticText7;
		wxRadioBox* rb_v2cmethod;
		wxCheckBox* cb_v2cmonitor;
		wxCheckBox* cb_v2clauncher;
		wxStaticText* m_staticText35;
		wxCheckBox* cb_dict;
		wxStaticLine* m_staticline2;
		wxStaticText* m_staticText81;
		wxSpinCtrl* sp_apmistake;
		wxStaticText* m_staticText15;
		wxSpinCtrl* sp_apsec;
		wxStaticText* m_staticText16;
		wxCheckBox* cb_apscore;
		wxCheckBox* cb_aptime;
		wxCheckBox* cb_apsp;
		wxStaticText* m_staticText17;
		wxSpinCtrl* sp_aupsec;
		wxStaticText* m_staticText20;
		wxStaticLine* m_staticline21;
		wxStaticText* m_staticText91;
		wxStaticText* m_staticText112;
		wxChoice* c_notstyle;
		wxStaticText* m_staticText13;
		wxSpinCtrl* sp_notdelay;
		wxCheckBox* cb_notpretrig;
		wxStaticText* m_staticText44;
		wxCheckBox* cb_oscenable;
		wxStaticText* m_staticText45;
		wxTextCtrl* tc_oschost;
		wxStaticText* m_staticText1311;
		wxSpinCtrl* sp_oscport;
		wxStaticText* m_staticText131;
		wxChoice* c_oscprotocol;
		wxCheckBox* cb_oscrecognition;
		wxPanel* p_engine;
		wxStaticText* m_staticText24;
		wxCheckBox* cb_engdefault;
		wxStaticText* m_staticText29;
		wxSpinCtrl* sp_engthreshold;
		wxStaticText* m_staticText30;
		wxSpinCtrl* sp_engzero;
		wxCheckBox* cb_engnostrip;
		wxCheckBox* cb_engzmean;
		wxStaticLine* m_staticline9;
		wxStaticText* m_staticText25;
		wxStaticText* m_staticText31;
		wxChoice* c_enggprune;
		wxStaticText* m_staticText32;
		wxChoice* c_engiwcd1;
		wxSpinCtrl* sp_engiwcd1;
		wxStaticText* m_staticText261;
		wxSpinCtrl* sp_engtmix;
		wxStaticLine* m_staticline10;
		wxStaticText* m_staticText26;
		wxStaticText* m_staticText271;
		wxSpinCtrl* sp_engbeam;
		wxStaticText* m_staticText28;
		wxTextCtrl* tc_engpenalty;
		
		wxStaticText* m_staticText48;
		wxButton* b_restartjulius;
		wxPanel* p_audio;
		wxStaticText* m_staticText351;
		wxChoice* c_driver;
		wxStaticText* m_staticText42;
		wxGauge* g_englevel;
		wxStaticText* st_db;
		wxStaticLine* m_staticline7;
		wxStaticText* m_staticText36;
		wxStaticText* st_volume;
		wxSlider* s_volume;
		
		wxStaticText* m_staticText43;
		wxChoice* c_filter;
		wxStaticText* m_staticText40;
		wxStaticText* st_lp;
		wxSlider* s_lp;
		wxStaticText* m_staticText401;
		wxStaticText* st_hp;
		wxSlider* s_hp;
		wxStaticLine* m_staticline91;
		wxStaticText* m_staticText37;
		wxButton* b_spectrum1;
		wxPanel* p_language;
		wxStaticText* st_language_select;
		wxChoice* c_language;
		wxButton* b_languagedownload;
		
		wxStaticText* st_languagedownloading;
		wxGauge* g_languagedownloading;
		wxStaticLine* m_staticline6;
		wxHtmlWindow* html_language;
		wxPanel* p_help;
		wxHtmlWindow* html_help;
		wxStatusBar* sb;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseFrame( wxCloseEvent& event ) { event.Skip(); }
		virtual void Onm_nb( wxNotebookEvent& event ) { event.Skip(); }
		virtual void Oncb_pause( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onb_update( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onm_prefupdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onb_activeword( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onm_nbv2c( wxNotebookEvent& event ) { event.Skip(); }
		virtual void Onpb_v2capplication( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onpc_v2capplication( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void Onb_v2capplicationedit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLink( wxHtmlLinkEvent& event ) { event.Skip(); }
		virtual void Onpb_v2cshortcut( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onpc_v2cshortcut( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void Onpb_v2cshortcutedit( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onpc_v2cimportapp( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onb_v2cimportapp( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onpc_v2cimportshortcut( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onb_v2cimportshortcut( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onrb_v2cmethod( wxCommandEvent& event ) { event.Skip(); }
		virtual void Oncb_v2cmonitor( wxCommandEvent& event ) { event.Skip(); }
		virtual void Oncb_v2clauncher( wxCommandEvent& event ) { event.Skip(); }
		virtual void Oncb_dict( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onc_notification( wxCommandEvent& event ) { event.Skip(); }
		virtual void Oncb_oscenable( wxCommandEvent& event ) { event.Skip(); }
		virtual void Oncb_engdefault( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onsp_engthreshold( wxSpinEvent& event ) { event.Skip(); }
		virtual void Onsp_engzero( wxSpinEvent& event ) { event.Skip(); }
		virtual void Oncb_engnostrip( wxCommandEvent& event ) { event.Skip(); }
		virtual void Oncb_engzmean( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onc_enggprune( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onc_engiwcd1( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onsp_engiwcd1( wxSpinEvent& event ) { event.Skip(); }
		virtual void Onsp_engtmix( wxSpinEvent& event ) { event.Skip(); }
		virtual void Onsp_engbeam( wxSpinEvent& event ) { event.Skip(); }
		virtual void Ontc_engpenalty( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onb_restartjulius( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onc_driver( wxCommandEvent& event ) { event.Skip(); }
		virtual void Ons_volume( wxScrollEvent& event ) { event.Skip(); }
		virtual void Onc_filter( wxCommandEvent& event ) { event.Skip(); }
		virtual void Ons_lp( wxScrollEvent& event ) { event.Skip(); }
		virtual void Ons_hp( wxScrollEvent& event ) { event.Skip(); }
		virtual void Onb_spectrum( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onb_languagedownload( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("kiku"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 620,420 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~MainFrameBase();
	
};

#endif //__gui__
