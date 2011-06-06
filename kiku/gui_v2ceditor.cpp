///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 11 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui_v2ceditor.h"

///////////////////////////////////////////////////////////////////////////

gui_v2ceditor::gui_v2ceditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 5, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("Notification:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer1->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_notification = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	tc_notification->SetMinSize( wxSize( 300,-1 ) );
	
	fgSizer1->Add( tc_notification, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, _("Pre-trig:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer1->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_pretrig = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( tc_pretrig, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("Trig:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer1->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_trig = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( tc_trig, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("Command:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer1->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_command = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( tc_command, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer1->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString c_typeChoices[] = { _("xdotool"), _("shell"), _("gnome"), _("kiku") };
	int c_typeNChoices = sizeof( c_typeChoices ) / sizeof( wxString );
	c_type = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, c_typeNChoices, c_typeChoices, 0 );
	c_type->SetSelection( 0 );
	c_type->SetMinSize( wxSize( 300,-1 ) );
	
	fgSizer1->Add( c_type, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	bSizer3->Add( fgSizer1, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer3->Add( 0, 0, 0, 0, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer3->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	b_add = new wxButton( this, wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	b_add->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer4->Add( b_add, 0, wxALL, 5 );
	
	b_delete = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	b_delete->Hide();
	
	bSizer4->Add( b_delete, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	bSizer3->Add( bSizer4, 0, 0, 5 );
	
	mainSizer->Add( bSizer3, 1, wxEXPAND, 5 );
	
	html_v2ceditor = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSIMPLE_BORDER );
	mainSizer->Add( html_v2ceditor, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	b_add->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2ceditor::Onb_add ), NULL, this );
	b_delete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2ceditor::Onb_delete ), NULL, this );
}

gui_v2ceditor::~gui_v2ceditor()
{
	// Disconnect Events
	b_add->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2ceditor::Onb_add ), NULL, this );
	b_delete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2ceditor::Onb_delete ), NULL, this );
	
}
