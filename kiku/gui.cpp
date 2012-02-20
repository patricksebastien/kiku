///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 19 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 620,420 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_nb = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	p_recognition = new wxPanel( m_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( p_recognition, wxID_ANY, _("Word:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer4->Add( m_staticText1, 0, wxALL, 5 );
	
	tcro_word = new wxTextCtrl( p_recognition, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer4->Add( tcro_word, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer3->Add( bSizer4, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText11 = new wxStaticText( p_recognition, wxID_ANY, _("Pronunciation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	m_staticText11->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer5->Add( m_staticText11, 0, wxALL, 5 );
	
	tcro_pronun = new wxTextCtrl( p_recognition, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer5->Add( tcro_pronun, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer3->Add( bSizer5, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText111 = new wxStaticText( p_recognition, wxID_ANY, _("Score:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	m_staticText111->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer7->Add( m_staticText111, 0, wxALL, 5 );
	
	tcro_score = new wxTextCtrl( p_recognition, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), wxTE_MULTILINE|wxTE_READONLY );
	bSizer7->Add( tcro_score, 1, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer3->Add( bSizer7, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	cb_pause = new wxCheckBox( p_recognition, wxID_ANY, _("Pause"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	bSizer8->Add( cb_pause, 0, wxALIGN_RIGHT|wxBOTTOM|wxTOP, 5 );
	
	wxBoxSizer* sizer_update;
	sizer_update = new wxBoxSizer( wxHORIZONTAL );
	
	bm_update = new wxStaticBitmap( p_recognition, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	sizer_update->Add( bm_update, 0, wxALIGN_BOTTOM|wxALL, 5 );
	
	b_update = new wxButton( p_recognition, wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	sizer_update->Add( b_update, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );
	
	
	bSizer8->Add( sizer_update, 0, 0, 5 );
	
	
	bSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText8 = new wxStaticText( p_recognition, wxID_ANY, _("Score threshold:"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer8->Add( m_staticText8, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	tc_scorethres = new wxTextCtrl( p_recognition, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer9->Add( tc_scorethres, 0, wxLEFT, 5 );
	
	
	bSizer8->Add( bSizer9, 0, 0, 5 );
	
	m_staticText9 = new wxStaticText( p_recognition, wxID_ANY, _("Minimum length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer8->Add( m_staticText9, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	sp_minlength = new wxSpinCtrl( p_recognition, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, 1, 100000, 0 );
	bSizer8->Add( sp_minlength, 0, wxLEFT, 5 );
	
	m_staticText10 = new wxStaticText( p_recognition, wxID_ANY, _("Maximum length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer8->Add( m_staticText10, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	sp_maxlength = new wxSpinCtrl( p_recognition, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, 2, 100000, 0 );
	bSizer8->Add( sp_maxlength, 0, wxBOTTOM|wxLEFT, 5 );
	
	b_activeword = new wxButton( p_recognition, wxID_ANY, _("Active word"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( b_activeword, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	
	bSizer3->Add( bSizer8, 0, wxEXPAND, 5 );
	
	
	p_recognition->SetSizer( bSizer3 );
	p_recognition->Layout();
	bSizer3->Fit( p_recognition );
	m_nb->AddPage( p_recognition, _("Recognition"), true );
	p_V2C = new wxPanel( m_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxVERTICAL );
	
	m_nbv2c = new wxNotebook( p_V2C, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_LEFT );
	p_v2capplication = new wxPanel( m_nbv2c, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer361;
	bSizer361 = new wxBoxSizer( wxVERTICAL );
	
	pb_v2capplication = new wxButton( p_v2capplication, wxID_ANY, _("  Add an application  "), wxDefaultPosition, wxDefaultSize, 0 );
	pb_v2capplication->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer361->Add( pb_v2capplication, 0, wxALL, 5 );
	
	st_defined = new wxStaticText( p_v2capplication, wxID_ANY, _(" Defined:"), wxDefaultPosition, wxDefaultSize, 0 );
	st_defined->Wrap( -1 );
	bSizer361->Add( st_defined, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxBoxSizer* bSizer371;
	bSizer371 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString pc_v2capplicationChoices;
	pc_v2capplication = new wxChoice( p_v2capplication, wxID_ANY, wxDefaultPosition, wxDefaultSize, pc_v2capplicationChoices, 0 );
	pc_v2capplication->SetSelection( 0 );
	bSizer371->Add( pc_v2capplication, 1, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT, 5 );
	
	pb_v2capplicationedit = new wxButton( p_v2capplication, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer371->Add( pb_v2capplicationedit, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer361->Add( bSizer371, 0, wxEXPAND, 5 );
	
	html_v2capplication = new wxHtmlWindow( p_v2capplication, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSIMPLE_BORDER );
	bSizer361->Add( html_v2capplication, 1, wxALL|wxEXPAND, 5 );
	
	
	p_v2capplication->SetSizer( bSizer361 );
	p_v2capplication->Layout();
	bSizer361->Fit( p_v2capplication );
	m_nbv2c->AddPage( p_v2capplication, _("Application"), true );
	p_v2cshortcut = new wxPanel( m_nbv2c, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer362;
	bSizer362 = new wxBoxSizer( wxVERTICAL );
	
	pb_v2cshortcut = new wxButton( p_v2cshortcut, wxID_ANY, _("  Add a shortcut  "), wxDefaultPosition, wxDefaultSize, 0 );
	pb_v2cshortcut->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer362->Add( pb_v2cshortcut, 0, wxALL, 5 );
	
	st_shortcutdefined = new wxStaticText( p_v2cshortcut, wxID_ANY, _(" Defined:"), wxDefaultPosition, wxDefaultSize, 0 );
	st_shortcutdefined->Wrap( -1 );
	bSizer362->Add( st_shortcutdefined, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxBoxSizer* bSizer372;
	bSizer372 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString pc_v2cshortcutChoices;
	pc_v2cshortcut = new wxChoice( p_v2cshortcut, wxID_ANY, wxDefaultPosition, wxDefaultSize, pc_v2cshortcutChoices, 0 );
	pc_v2cshortcut->SetSelection( 0 );
	bSizer372->Add( pc_v2cshortcut, 1, wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	pb_v2cshortcutedit = new wxButton( p_v2cshortcut, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer372->Add( pb_v2cshortcutedit, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer362->Add( bSizer372, 0, wxEXPAND, 5 );
	
	html_v2cshortcut = new wxHtmlWindow( p_v2cshortcut, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSIMPLE_BORDER );
	bSizer362->Add( html_v2cshortcut, 1, wxALL|wxEXPAND, 5 );
	
	
	p_v2cshortcut->SetSizer( bSizer362 );
	p_v2cshortcut->Layout();
	bSizer362->Fit( p_v2cshortcut );
	m_nbv2c->AddPage( p_v2cshortcut, _("Shortcut"), false );
	p_v2cimport = new wxPanel( m_nbv2c, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText33 = new wxStaticText( p_v2cimport, wxID_ANY, _("Application:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	bSizer38->Add( m_staticText33, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString pc_v2cimportappChoices;
	pc_v2cimportapp = new wxChoice( p_v2cimport, wxID_ANY, wxDefaultPosition, wxDefaultSize, pc_v2cimportappChoices, 0 );
	pc_v2cimportapp->SetSelection( 0 );
	bSizer40->Add( pc_v2cimportapp, 1, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT, 5 );
	
	b_v2cimportapp = new wxButton( p_v2cimport, wxID_ANY, _("Download"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( b_v2cimportapp, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer38->Add( bSizer40, 0, wxEXPAND, 5 );
	
	m_staticText34 = new wxStaticText( p_v2cimport, wxID_ANY, _("Shortcut:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	bSizer38->Add( m_staticText34, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer401;
	bSizer401 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString pc_v2cimportshortcutChoices;
	pc_v2cimportshortcut = new wxChoice( p_v2cimport, wxID_ANY, wxDefaultPosition, wxDefaultSize, pc_v2cimportshortcutChoices, 0 );
	pc_v2cimportshortcut->SetSelection( 0 );
	bSizer401->Add( pc_v2cimportshortcut, 1, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT, 5 );
	
	b_v2cimportshortcut = new wxButton( p_v2cimport, wxID_ANY, _("Download"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer401->Add( b_v2cimportshortcut, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer38->Add( bSizer401, 0, wxEXPAND, 5 );
	
	html_import = new wxHtmlWindow( p_v2cimport, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSIMPLE_BORDER );
	bSizer38->Add( html_import, 1, wxALL|wxEXPAND, 5 );
	
	
	p_v2cimport->SetSizer( bSizer38 );
	p_v2cimport->Layout();
	bSizer38->Fit( p_v2cimport );
	m_nbv2c->AddPage( p_v2cimport, _("Import"), false );
	
	bSizer34->Add( m_nbv2c, 1, wxEXPAND | wxALL, 5 );
	
	
	p_V2C->SetSizer( bSizer34 );
	p_V2C->Layout();
	bSizer34->Fit( p_V2C );
	m_nb->AddPage( p_V2C, _("  V2C  "), false );
	p_configutation = new wxPanel( m_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText7 = new wxStaticText( p_configutation, wxID_ANY, _("V2C loading:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	m_staticText7->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer10->Add( m_staticText7, 0, wxALL, 5 );
	
	wxString rb_v2cmethodChoices[] = { _("All"), _("Match") };
	int rb_v2cmethodNChoices = sizeof( rb_v2cmethodChoices ) / sizeof( wxString );
	rb_v2cmethod = new wxRadioBox( p_configutation, wxID_ANY, _("Method"), wxDefaultPosition, wxDefaultSize, rb_v2cmethodNChoices, rb_v2cmethodChoices, 1, wxRA_SPECIFY_COLS );
	rb_v2cmethod->SetSelection( 0 );
	bSizer10->Add( rb_v2cmethod, 0, wxALL|wxEXPAND, 5 );
	
	cb_v2cmonitor = new wxCheckBox( p_configutation, wxID_ANY, _("Monitor process"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( cb_v2cmonitor, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	cb_v2clauncher = new wxCheckBox( p_configutation, wxID_ANY, _("Launcher"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( cb_v2clauncher, 0, wxALL, 5 );
	
	m_staticText35 = new wxStaticText( p_configutation, wxID_ANY, _("Dictionary:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	m_staticText35->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer10->Add( m_staticText35, 0, wxALL, 5 );
	
	cb_dict = new wxCheckBox( p_configutation, wxID_ANY, _("Match V2C"), wxDefaultPosition, wxDefaultSize, 0 );
	cb_dict->SetValue(true); 
	bSizer10->Add( cb_dict, 0, wxALL, 5 );
	
	
	bSizer91->Add( bSizer10, 0, 0, 5 );
	
	m_staticline2 = new wxStaticLine( p_configutation, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer91->Add( m_staticline2, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText81 = new wxStaticText( p_configutation, wxID_ANY, _("Automatic pause:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	m_staticText81->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer11->Add( m_staticText81, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	sp_apmistake = new wxSpinCtrl( p_configutation, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 2, 50, 0 );
	bSizer18->Add( sp_apmistake, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_staticText15 = new wxStaticText( p_configutation, wxID_ANY, _("mistakes in"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	bSizer18->Add( m_staticText15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	sp_apsec = new wxSpinCtrl( p_configutation, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 120, 1 );
	sp_apsec->SetMinSize( wxSize( 60,-1 ) );
	
	bSizer18->Add( sp_apsec, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );
	
	m_staticText16 = new wxStaticText( p_configutation, wxID_ANY, _("sec."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer18->Add( m_staticText16, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	
	bSizer11->Add( bSizer18, 0, 0, 5 );
	
	cb_apscore = new wxCheckBox( p_configutation, wxID_ANY, _("Score"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( cb_apscore, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	cb_aptime = new wxCheckBox( p_configutation, wxID_ANY, _("Time"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( cb_aptime, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	cb_apsp = new wxCheckBox( p_configutation, wxID_ANY, _("SP"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( cb_apsp, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer11->Add( bSizer23, 1, wxEXPAND, 5 );
	
	m_staticText17 = new wxStaticText( p_configutation, wxID_ANY, _("Automatic unpause:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	m_staticText17->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer11->Add( m_staticText17, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	sp_aupsec = new wxSpinCtrl( p_configutation, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 2, 300, 0 );
	bSizer22->Add( sp_aupsec, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT, 5 );
	
	m_staticText20 = new wxStaticText( p_configutation, wxID_ANY, _("seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	bSizer22->Add( m_staticText20, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer11->Add( bSizer22, 0, 0, 5 );
	
	
	bSizer91->Add( bSizer11, 0, 0, 5 );
	
	m_staticline21 = new wxStaticLine( p_configutation, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer91->Add( m_staticline21, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText91 = new wxStaticText( p_configutation, wxID_ANY, _("Notification:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText91->Wrap( -1 );
	m_staticText91->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer12->Add( m_staticText91, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText112 = new wxStaticText( p_configutation, wxID_ANY, _("Style:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText112->Wrap( -1 );
	bSizer13->Add( m_staticText112, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxString c_notstyleChoices[] = { _("None"), _("Built-in"), _("Notify"), _("XOSD") };
	int c_notstyleNChoices = sizeof( c_notstyleChoices ) / sizeof( wxString );
	c_notstyle = new wxChoice( p_configutation, wxID_ANY, wxDefaultPosition, wxDefaultSize, c_notstyleNChoices, c_notstyleChoices, 0 );
	c_notstyle->SetSelection( 0 );
	bSizer13->Add( c_notstyle, 0, wxALL, 5 );
	
	
	bSizer12->Add( bSizer13, 0, wxRIGHT, 5 );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText13 = new wxStaticText( p_configutation, wxID_ANY, _("Delay:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	bSizer16->Add( m_staticText13, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	sp_notdelay = new wxSpinCtrl( p_configutation, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 78,-1 ), wxSP_ARROW_KEYS, 1, 10, 0 );
	bSizer16->Add( sp_notdelay, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer12->Add( bSizer16, 0, wxRIGHT, 5 );
	
	cb_notpretrig = new wxCheckBox( p_configutation, wxID_ANY, _("Show pretrigger:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	cb_notpretrig->SetValue(true); 
	bSizer12->Add( cb_notpretrig, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_staticText44 = new wxStaticText( p_configutation, wxID_ANY, _("Open Sound Control:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( -1 );
	m_staticText44->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer12->Add( m_staticText44, 0, wxALL, 5 );
	
	cb_oscenable = new wxCheckBox( p_configutation, wxID_ANY, _("Enable client"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( cb_oscenable, 0, wxALL, 5 );
	
	m_staticText45 = new wxStaticText( p_configutation, wxID_ANY, _("Host:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	bSizer12->Add( m_staticText45, 0, wxRIGHT|wxLEFT, 5 );
	
	tc_oschost = new wxTextCtrl( p_configutation, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( tc_oschost, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer1611;
	bSizer1611 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1311 = new wxStaticText( p_configutation, wxID_ANY, _("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1311->Wrap( -1 );
	bSizer1611->Add( m_staticText1311, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	sp_oscport = new wxSpinCtrl( p_configutation, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 78,-1 ), wxSP_ARROW_KEYS, 1, 999999, 0 );
	bSizer1611->Add( sp_oscport, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer12->Add( bSizer1611, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer161;
	bSizer161 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText131 = new wxStaticText( p_configutation, wxID_ANY, _("Protocol:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText131->Wrap( -1 );
	bSizer161->Add( m_staticText131, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	wxString c_oscprotocolChoices[] = { _("UDP"), _("TCP"), _("UNIX") };
	int c_oscprotocolNChoices = sizeof( c_oscprotocolChoices ) / sizeof( wxString );
	c_oscprotocol = new wxChoice( p_configutation, wxID_ANY, wxDefaultPosition, wxDefaultSize, c_oscprotocolNChoices, c_oscprotocolChoices, 0 );
	c_oscprotocol->SetSelection( 0 );
	bSizer161->Add( c_oscprotocol, 1, wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	
	bSizer12->Add( bSizer161, 1, wxEXPAND, 5 );
	
	cb_oscrecognition = new wxCheckBox( p_configutation, wxID_ANY, _("Send recognition"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( cb_oscrecognition, 0, wxALL, 5 );
	
	
	bSizer91->Add( bSizer12, 0, 0, 5 );
	
	
	p_configutation->SetSizer( bSizer91 );
	p_configutation->Layout();
	bSizer91->Fit( p_configutation );
	m_nb->AddPage( p_configutation, _("Configuration"), false );
	p_engine = new wxPanel( m_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText24 = new wxStaticText( p_engine, wxID_ANY, _("Detection:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	m_staticText24->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer25->Add( m_staticText24, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );
	
	cb_engdefault = new wxCheckBox( p_engine, wxID_ANY, _("Default"), wxDefaultPosition, wxDefaultSize, 0 );
	cb_engdefault->SetValue(true); 
	bSizer30->Add( cb_engdefault, 0, wxALL, 5 );
	
	m_staticText29 = new wxStaticText( p_engine, wxID_ANY, _("Threshold"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	bSizer30->Add( m_staticText29, 0, wxALL, 5 );
	
	sp_engthreshold = new wxSpinCtrl( p_engine, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 32767, 0 );
	bSizer30->Add( sp_engthreshold, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	m_staticText30 = new wxStaticText( p_engine, wxID_ANY, _("Zero crossing:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	bSizer30->Add( m_staticText30, 0, wxALL, 5 );
	
	sp_engzero = new wxSpinCtrl( p_engine, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000, 0 );
	bSizer30->Add( sp_engzero, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	cb_engnostrip = new wxCheckBox( p_engine, wxID_ANY, _("No strip"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer30->Add( cb_engnostrip, 0, wxALL, 5 );
	
	cb_engzmean = new wxCheckBox( p_engine, wxID_ANY, _("ZMean"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer30->Add( cb_engzmean, 0, wxALL, 5 );
	
	
	bSizer29->Add( bSizer30, 0, wxEXPAND, 5 );
	
	
	bSizer25->Add( bSizer29, 1, wxEXPAND, 5 );
	
	
	bSizer24->Add( bSizer25, 1, wxEXPAND, 5 );
	
	m_staticline9 = new wxStaticLine( p_engine, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer24->Add( m_staticline9, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText25 = new wxStaticText( p_engine, wxID_ANY, _("Acoustic model:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	m_staticText25->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer26->Add( m_staticText25, 0, wxALL, 5 );
	
	m_staticText31 = new wxStaticText( p_engine, wxID_ANY, _("GPrune:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	bSizer26->Add( m_staticText31, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );
	
	wxString c_enggpruneChoices[] = { _("safe"), _("heuristic"), _("beam"), _("none"), _("default") };
	int c_enggpruneNChoices = sizeof( c_enggpruneChoices ) / sizeof( wxString );
	c_enggprune = new wxChoice( p_engine, wxID_ANY, wxDefaultPosition, wxDefaultSize, c_enggpruneNChoices, c_enggpruneChoices, 0 );
	c_enggprune->SetSelection( 0 );
	bSizer32->Add( c_enggprune, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer26->Add( bSizer32, 0, 0, 5 );
	
	m_staticText32 = new wxStaticText( p_engine, wxID_ANY, _("Iwcd1:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	bSizer26->Add( m_staticText32, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	wxString c_engiwcd1Choices[] = { _("avg"), _("max"), _("best") };
	int c_engiwcd1NChoices = sizeof( c_engiwcd1Choices ) / sizeof( wxString );
	c_engiwcd1 = new wxChoice( p_engine, wxID_ANY, wxDefaultPosition, wxDefaultSize, c_engiwcd1NChoices, c_engiwcd1Choices, 0 );
	c_engiwcd1->SetSelection( 0 );
	bSizer31->Add( c_engiwcd1, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	sp_engiwcd1 = new wxSpinCtrl( p_engine, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0 );
	sp_engiwcd1->SetMinSize( wxSize( 60,-1 ) );
	
	bSizer31->Add( sp_engiwcd1, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizer26->Add( bSizer31, 0, 0, 5 );
	
	m_staticText261 = new wxStaticText( p_engine, wxID_ANY, _("TMix:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText261->Wrap( -1 );
	bSizer26->Add( m_staticText261, 0, wxALL, 5 );
	
	sp_engtmix = new wxSpinCtrl( p_engine, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0 );
	bSizer26->Add( sp_engtmix, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer24->Add( bSizer26, 1, 0, 5 );
	
	m_staticline10 = new wxStaticLine( p_engine, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer24->Add( m_staticline10, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText26 = new wxStaticText( p_engine, wxID_ANY, _("First pass:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	m_staticText26->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer27->Add( m_staticText26, 0, wxALL, 5 );
	
	m_staticText271 = new wxStaticText( p_engine, wxID_ANY, _("Beam:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText271->Wrap( -1 );
	bSizer27->Add( m_staticText271, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer( wxHORIZONTAL );
	
	sp_engbeam = new wxSpinCtrl( p_engine, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100000, 0 );
	bSizer48->Add( sp_engbeam, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	cb_beammax = new wxCheckBox( p_engine, wxID_ANY, _("Max"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer48->Add( cb_beammax, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer27->Add( bSizer48, 0, 0, 5 );
	
	m_staticText28 = new wxStaticText( p_engine, wxID_ANY, _("Penalty:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	bSizer27->Add( m_staticText28, 0, wxALL, 5 );
	
	tc_engpenalty = new wxTextCtrl( p_engine, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer27->Add( tc_engpenalty, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer27->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText48 = new wxStaticText( p_engine, wxID_ANY, _("Version: 0.4"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	bSizer27->Add( m_staticText48, 0, wxALIGN_RIGHT|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	b_restartjulius = new wxButton( p_engine, wxID_ANY, _("Restart Engine"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer27->Add( b_restartjulius, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	
	bSizer24->Add( bSizer27, 1, wxEXPAND, 5 );
	
	
	p_engine->SetSizer( bSizer24 );
	p_engine->Layout();
	bSizer24->Fit( p_engine );
	m_nb->AddPage( p_engine, _("Engine"), false );
	p_audio = new wxPanel( m_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer402;
	bSizer402 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText351 = new wxStaticText( p_audio, wxID_ANY, _("Driver:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText351->Wrap( -1 );
	m_staticText351->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer41->Add( m_staticText351, 0, wxALL, 5 );
	
	wxString c_driverChoices[] = { _("PulseAudio"), _("PulseAudio (monitor)"), _("Alsa") };
	int c_driverNChoices = sizeof( c_driverChoices ) / sizeof( wxString );
	c_driver = new wxChoice( p_audio, wxID_ANY, wxDefaultPosition, wxDefaultSize, c_driverNChoices, c_driverChoices, 0 );
	c_driver->SetSelection( 0 );
	bSizer41->Add( c_driver, 0, wxALL, 5 );
	
	m_staticText42 = new wxStaticText( p_audio, wxID_ANY, _("Audio Meter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	m_staticText42->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer41->Add( m_staticText42, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer45;
	bSizer45 = new wxBoxSizer( wxHORIZONTAL );
	
	g_englevel = new wxGauge( p_audio, wxID_ANY, 100, wxDefaultPosition, wxSize( 100,-1 ), wxGA_VERTICAL );
	bSizer45->Add( g_englevel, 1, wxALL|wxEXPAND, 5 );
	
	st_db = new wxStaticText( p_audio, wxID_ANY, _("40 dB"), wxDefaultPosition, wxDefaultSize, 0 );
	st_db->Wrap( -1 );
	bSizer45->Add( st_db, 0, wxALL, 5 );
	
	
	bSizer41->Add( bSizer45, 1, 0, 5 );
	
	
	bSizer402->Add( bSizer41, 0, wxEXPAND, 5 );
	
	m_staticline7 = new wxStaticLine( p_audio, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer402->Add( m_staticline7, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText36 = new wxStaticText( p_audio, wxID_ANY, _("Volume:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	m_staticText36->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer42->Add( m_staticText36, 0, wxALL, 5 );
	
	st_volume = new wxStaticText( p_audio, wxID_ANY, _("100%"), wxDefaultPosition, wxDefaultSize, 0 );
	st_volume->Wrap( -1 );
	bSizer42->Add( st_volume, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	s_volume = new wxSlider( p_audio, wxID_ANY, 100, 0, 200, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer42->Add( s_volume, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	bSizer42->Add( 0, 0, 0, wxTOP|wxBOTTOM, 5 );
	
	m_staticText43 = new wxStaticText( p_audio, wxID_ANY, _("Filter:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	m_staticText43->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer42->Add( m_staticText43, 0, wxALL, 5 );
	
	wxString c_filterChoices[] = { _("None"), _("1-order"), _("2-order (butterworth)") };
	int c_filterNChoices = sizeof( c_filterChoices ) / sizeof( wxString );
	c_filter = new wxChoice( p_audio, wxID_ANY, wxDefaultPosition, wxDefaultSize, c_filterNChoices, c_filterChoices, 0 );
	c_filter->SetSelection( 0 );
	bSizer42->Add( c_filter, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer44;
	bSizer44 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText40 = new wxStaticText( p_audio, wxID_ANY, _("Low pass:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	bSizer44->Add( m_staticText40, 0, wxALL, 5 );
	
	st_lp = new wxStaticText( p_audio, wxID_ANY, _("300 hertz"), wxDefaultPosition, wxDefaultSize, 0 );
	st_lp->Wrap( -1 );
	bSizer44->Add( st_lp, 0, wxALL, 5 );
	
	
	bSizer42->Add( bSizer44, 0, 0, 5 );
	
	s_lp = new wxSlider( p_audio, wxID_ANY, 50, 3000, 20000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer42->Add( s_lp, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer441;
	bSizer441 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText401 = new wxStaticText( p_audio, wxID_ANY, _("High pass:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText401->Wrap( -1 );
	bSizer441->Add( m_staticText401, 0, wxALL, 5 );
	
	st_hp = new wxStaticText( p_audio, wxID_ANY, _("300 hertz"), wxDefaultPosition, wxDefaultSize, 0 );
	st_hp->Wrap( -1 );
	bSizer441->Add( st_hp, 0, wxALL, 5 );
	
	
	bSizer42->Add( bSizer441, 0, 0, 5 );
	
	s_hp = new wxSlider( p_audio, wxID_ANY, 50, 5, 2999, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer42->Add( s_hp, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer402->Add( bSizer42, 1, wxEXPAND, 5 );
	
	m_staticline91 = new wxStaticLine( p_audio, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer402->Add( m_staticline91, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText37 = new wxStaticText( p_audio, wxID_ANY, _("Noise:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	m_staticText37->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer43->Add( m_staticText37, 0, wxALL, 5 );
	
	b_spectrum1 = new wxButton( p_audio, wxID_ANY, _("Calculate Spectrum"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer43->Add( b_spectrum1, 0, wxALL, 5 );
	
	
	bSizer402->Add( bSizer43, 0, wxEXPAND, 5 );
	
	
	p_audio->SetSizer( bSizer402 );
	p_audio->Layout();
	bSizer402->Fit( p_audio );
	m_nb->AddPage( p_audio, _("Audio"), false );
	p_language = new wxPanel( m_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer291;
	bSizer291 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer301;
	bSizer301 = new wxBoxSizer( wxVERTICAL );
	
	st_language_select = new wxStaticText( p_language, wxID_ANY, _("Select a language:"), wxDefaultPosition, wxDefaultSize, 0 );
	st_language_select->Wrap( -1 );
	st_language_select->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer301->Add( st_language_select, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer321;
	bSizer321 = new wxBoxSizer( wxHORIZONTAL );
	
	wxString c_languageChoices[] = { _("English 14k [VoxForge]"), _("German 370k [VoxForge]"), _("Japanese 20k [Julius]"), _("Japanese 60k [Julius]"), _("Portuguese 65k [Fala Brasil]") };
	int c_languageNChoices = sizeof( c_languageChoices ) / sizeof( wxString );
	c_language = new wxChoice( p_language, wxID_ANY, wxDefaultPosition, wxDefaultSize, c_languageNChoices, c_languageChoices, 0 );
	c_language->SetSelection( 0 );
	bSizer321->Add( c_language, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT, 5 );
	
	b_languagedownload = new wxButton( p_language, wxID_ANY, _("Download"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer321->Add( b_languagedownload, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer301->Add( bSizer321, 0, 0, 5 );
	
	
	bSizer301->Add( 0, 20, 0, 0, 5 );
	
	st_languagedownloading = new wxStaticText( p_language, wxID_ANY, _("Downloading..."), wxDefaultPosition, wxDefaultSize, 0 );
	st_languagedownloading->Wrap( -1 );
	bSizer301->Add( st_languagedownloading, 0, wxALL, 5 );
	
	g_languagedownloading = new wxGauge( p_language, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	bSizer301->Add( g_languagedownloading, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer291->Add( bSizer301, 1, wxEXPAND, 5 );
	
	m_staticline6 = new wxStaticLine( p_language, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer291->Add( m_staticline6, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer311;
	bSizer311 = new wxBoxSizer( wxVERTICAL );
	
	html_language = new wxHtmlWindow( p_language, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSIMPLE_BORDER );
	bSizer311->Add( html_language, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer291->Add( bSizer311, 1, wxEXPAND, 5 );
	
	
	p_language->SetSizer( bSizer291 );
	p_language->Layout();
	bSizer291->Fit( p_language );
	m_nb->AddPage( p_language, _("Language"), false );
	p_help = new wxPanel( m_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer81;
	bSizer81 = new wxBoxSizer( wxVERTICAL );
	
	html_help = new wxHtmlWindow( p_help, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSIMPLE_BORDER );
	bSizer81->Add( html_help, 1, wxALL|wxEXPAND, 5 );
	
	
	p_help->SetSizer( bSizer81 );
	p_help->Layout();
	bSizer81->Fit( p_help );
	m_nb->AddPage( p_help, _("Help"), false );
	
	mainSizer->Add( m_nb, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	sb = this->CreateStatusBar( 3, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	m_nb->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( MainFrameBase::Onm_nb ), NULL, this );
	cb_pause->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_pause ), NULL, this );
	b_update->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_update ), NULL, this );
	tc_scorethres->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	sp_minlength->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	sp_maxlength->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	b_activeword->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_activeword ), NULL, this );
	m_nbv2c->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( MainFrameBase::Onm_nbv2c ), NULL, this );
	pb_v2capplication->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onpb_v2capplication ), NULL, this );
	pc_v2capplication->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::Onpc_v2capplication ), NULL, this );
	pb_v2capplicationedit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_v2capplicationedit ), NULL, this );
	html_v2capplication->Connect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( MainFrameBase::OnLink ), NULL, this );
	pb_v2cshortcut->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onpb_v2cshortcut ), NULL, this );
	pc_v2cshortcut->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::Onpc_v2cshortcut ), NULL, this );
	pb_v2cshortcutedit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onpb_v2cshortcutedit ), NULL, this );
	html_v2cshortcut->Connect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( MainFrameBase::OnLink ), NULL, this );
	pc_v2cimportapp->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onpc_v2cimportapp ), NULL, this );
	b_v2cimportapp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_v2cimportapp ), NULL, this );
	pc_v2cimportshortcut->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onpc_v2cimportshortcut ), NULL, this );
	b_v2cimportshortcut->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_v2cimportshortcut ), NULL, this );
	html_import->Connect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( MainFrameBase::OnLink ), NULL, this );
	rb_v2cmethod->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MainFrameBase::Onrb_v2cmethod ), NULL, this );
	cb_v2cmonitor->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_v2cmonitor ), NULL, this );
	cb_v2clauncher->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_v2clauncher ), NULL, this );
	cb_dict->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_dict ), NULL, this );
	sp_apmistake->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	sp_apsec->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_apscore->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_aptime->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_apsp->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	sp_aupsec->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	c_notstyle->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onc_notification ), NULL, this );
	sp_notdelay->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_notpretrig->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_oscenable->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_oscenable ), NULL, this );
	tc_oschost->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	sp_oscport->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	c_oscprotocol->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_oscrecognition->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_engdefault->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_engdefault ), NULL, this );
	sp_engthreshold->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MainFrameBase::Onsp_engthreshold ), NULL, this );
	sp_engzero->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MainFrameBase::Onsp_engzero ), NULL, this );
	cb_engnostrip->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_engnostrip ), NULL, this );
	cb_engzmean->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_engzmean ), NULL, this );
	c_enggprune->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onc_enggprune ), NULL, this );
	c_engiwcd1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onc_engiwcd1 ), NULL, this );
	sp_engiwcd1->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MainFrameBase::Onsp_engiwcd1 ), NULL, this );
	sp_engtmix->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MainFrameBase::Onsp_engtmix ), NULL, this );
	sp_engbeam->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MainFrameBase::Onsp_engbeam ), NULL, this );
	cb_beammax->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_beammax ), NULL, this );
	tc_engpenalty->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Ontc_engpenalty ), NULL, this );
	b_restartjulius->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_restartjulius ), NULL, this );
	c_driver->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onc_driver ), NULL, this );
	s_volume->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	c_filter->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onc_filter ), NULL, this );
	s_lp->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_hp->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	b_spectrum1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_spectrum ), NULL, this );
	b_languagedownload->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_languagedownload ), NULL, this );
	html_language->Connect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( MainFrameBase::OnLink ), NULL, this );
	html_help->Connect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( MainFrameBase::OnLink ), NULL, this );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	m_nb->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( MainFrameBase::Onm_nb ), NULL, this );
	cb_pause->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_pause ), NULL, this );
	b_update->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_update ), NULL, this );
	tc_scorethres->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	sp_minlength->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	sp_maxlength->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	b_activeword->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_activeword ), NULL, this );
	m_nbv2c->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( MainFrameBase::Onm_nbv2c ), NULL, this );
	pb_v2capplication->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onpb_v2capplication ), NULL, this );
	pc_v2capplication->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::Onpc_v2capplication ), NULL, this );
	pb_v2capplicationedit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_v2capplicationedit ), NULL, this );
	html_v2capplication->Disconnect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( MainFrameBase::OnLink ), NULL, this );
	pb_v2cshortcut->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onpb_v2cshortcut ), NULL, this );
	pc_v2cshortcut->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::Onpc_v2cshortcut ), NULL, this );
	pb_v2cshortcutedit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onpb_v2cshortcutedit ), NULL, this );
	html_v2cshortcut->Disconnect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( MainFrameBase::OnLink ), NULL, this );
	pc_v2cimportapp->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onpc_v2cimportapp ), NULL, this );
	b_v2cimportapp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_v2cimportapp ), NULL, this );
	pc_v2cimportshortcut->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onpc_v2cimportshortcut ), NULL, this );
	b_v2cimportshortcut->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_v2cimportshortcut ), NULL, this );
	html_import->Disconnect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( MainFrameBase::OnLink ), NULL, this );
	rb_v2cmethod->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MainFrameBase::Onrb_v2cmethod ), NULL, this );
	cb_v2cmonitor->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_v2cmonitor ), NULL, this );
	cb_v2clauncher->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_v2clauncher ), NULL, this );
	cb_dict->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_dict ), NULL, this );
	sp_apmistake->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	sp_apsec->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_apscore->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_aptime->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_apsp->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	sp_aupsec->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	c_notstyle->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onc_notification ), NULL, this );
	sp_notdelay->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_notpretrig->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_oscenable->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_oscenable ), NULL, this );
	tc_oschost->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	sp_oscport->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	c_oscprotocol->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_oscrecognition->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Onm_prefupdate ), NULL, this );
	cb_engdefault->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_engdefault ), NULL, this );
	sp_engthreshold->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MainFrameBase::Onsp_engthreshold ), NULL, this );
	sp_engzero->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MainFrameBase::Onsp_engzero ), NULL, this );
	cb_engnostrip->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_engnostrip ), NULL, this );
	cb_engzmean->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_engzmean ), NULL, this );
	c_enggprune->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onc_enggprune ), NULL, this );
	c_engiwcd1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onc_engiwcd1 ), NULL, this );
	sp_engiwcd1->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MainFrameBase::Onsp_engiwcd1 ), NULL, this );
	sp_engtmix->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MainFrameBase::Onsp_engtmix ), NULL, this );
	sp_engbeam->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MainFrameBase::Onsp_engbeam ), NULL, this );
	cb_beammax->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrameBase::Oncb_beammax ), NULL, this );
	tc_engpenalty->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrameBase::Ontc_engpenalty ), NULL, this );
	b_restartjulius->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_restartjulius ), NULL, this );
	c_driver->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onc_driver ), NULL, this );
	s_volume->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	s_volume->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrameBase::Ons_volume ), NULL, this );
	c_filter->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrameBase::Onc_filter ), NULL, this );
	s_lp->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_lp->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrameBase::Ons_lp ), NULL, this );
	s_hp->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	s_hp->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrameBase::Ons_hp ), NULL, this );
	b_spectrum1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_spectrum ), NULL, this );
	b_languagedownload->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::Onb_languagedownload ), NULL, this );
	html_language->Disconnect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( MainFrameBase::OnLink ), NULL, this );
	html_help->Disconnect( wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler( MainFrameBase::OnLink ), NULL, this );
	
}
