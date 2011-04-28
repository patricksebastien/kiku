///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 11 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui_activeword.h"

///////////////////////////////////////////////////////////////////////////

gui_activeword::gui_activeword( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel3 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	listctrl_launcher = new wxListCtrl( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VRULES );
	bSizer4->Add( listctrl_launcher, 1, wxALL|wxEXPAND, 5 );
	
	b_applicationrefresh11 = new wxButton( m_panel3, wxID_ANY, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( b_applicationrefresh11, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_panel3->SetSizer( bSizer4 );
	m_panel3->Layout();
	bSizer4->Fit( m_panel3 );
	m_notebook1->AddPage( m_panel3, _("Launcher"), false );
	m_panel1 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	listctrl_app = new wxListCtrl( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VRULES );
	bSizer2->Add( listctrl_app, 1, wxALL|wxEXPAND, 5 );
	
	b_applicationrefresh = new wxButton( m_panel1, wxID_ANY, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( b_applicationrefresh, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	m_notebook1->AddPage( m_panel1, _("Application"), true );
	m_panel2 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	listctrl_shortcut = new wxListCtrl( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VRULES );
	bSizer3->Add( listctrl_shortcut, 1, wxALL|wxEXPAND, 5 );
	
	b_applicationrefresh1 = new wxButton( m_panel2, wxID_ANY, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( b_applicationrefresh1, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_panel2->SetSizer( bSizer3 );
	m_panel2->Layout();
	bSizer3->Fit( m_panel2 );
	m_notebook1->AddPage( m_panel2, _("Shortcut"), false );
	
	mainSizer->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	b_applicationrefresh11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_activeword::Onb_applicationrefresh ), NULL, this );
	b_applicationrefresh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_activeword::Onb_applicationrefresh ), NULL, this );
	b_applicationrefresh1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_activeword::Onb_applicationrefresh ), NULL, this );
}

gui_activeword::~gui_activeword()
{
	// Disconnect Events
	b_applicationrefresh11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_activeword::Onb_applicationrefresh ), NULL, this );
	b_applicationrefresh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_activeword::Onb_applicationrefresh ), NULL, this );
	b_applicationrefresh1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_activeword::Onb_applicationrefresh ), NULL, this );
	
}
