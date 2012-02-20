///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 19 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui_v2capplication.h"

///////////////////////////////////////////////////////////////////////////

gui_v2capplication::gui_v2capplication( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sb_newaction;
	sb_newaction = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("New action") ), wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	st_processname = new wxStaticText( this, wxID_ANY, _("ProcessName:"), wxDefaultPosition, wxDefaultSize, 0 );
	st_processname->Wrap( -1 );
	st_processname->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer2->Add( st_processname, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_processname = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	tc_processname->SetValidator( wxTextValidator( wxFILTER_EXCLUDE_CHAR_LIST, &processnameval ) );
	
	bSizer2->Add( tc_processname, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );
	
	b_addaction = new wxButton( this, wxID_ANY, _("Add an action"), wxDefaultPosition, wxDefaultSize, 0 );
	b_addaction->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	b_addaction->Enable( false );
	
	bSizer2->Add( b_addaction, 0, wxALL, 5 );
	
	
	sb_newaction->Add( bSizer2, 1, wxEXPAND|wxALIGN_RIGHT, 5 );
	
	
	mainSizer->Add( sb_newaction, 0, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sb_edit;
	sb_edit = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Edit action") ), wxVERTICAL );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString c_editactionChoices;
	c_editaction = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( -1,28 ), c_editactionChoices, 0 );
	c_editaction->SetSelection( 0 );
	c_editaction->SetMinSize( wxSize( -1,28 ) );
	
	bSizer41->Add( c_editaction, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );
	
	b_editaction = new wxButton( this, wxID_ANY, _("Edit"), wxDefaultPosition, wxSize( -1,28 ), 0 );
	b_editaction->SetMinSize( wxSize( -1,28 ) );
	
	bSizer41->Add( b_editaction, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	sb_edit->Add( bSizer41, 0, wxTOP|wxBOTTOM|wxEXPAND, 5 );
	
	
	mainSizer->Add( sb_edit, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sb_launcher;
	sb_launcher = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Launcher (optional)") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 4, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Notification:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer1->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	tc_notification = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	tc_notification->Enable( false );
	
	fgSizer1->Add( tc_notification, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Pre-trigger:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer1->Add( m_staticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	tc_pretrig = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	tc_pretrig->Enable( false );
	
	fgSizer1->Add( tc_pretrig, 1, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("Trigger:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer1->Add( m_staticText6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	tc_trig = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	tc_trig->Enable( false );
	
	fgSizer1->Add( tc_trig, 1, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("Command:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer1->Add( m_staticText8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	tc_command = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	tc_command->Enable( false );
	
	fgSizer1->Add( tc_command, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND, 5 );
	
	
	sb_launcher->Add( fgSizer1, 1, wxEXPAND, 5 );
	
	
	mainSizer->Add( sb_launcher, 1, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* sb_b;
	sb_b = new wxBoxSizer( wxHORIZONTAL );
	
	b_save = new wxButton( this, wxID_ANY, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	b_save->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	b_save->Enable( false );
	
	sb_b->Add( b_save, 0, wxALL, 5 );
	
	b_cancel = new wxButton( this, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	sb_b->Add( b_cancel, 0, wxALL, 5 );
	
	
	sb_b->Add( 0, 0, 1, wxEXPAND, 5 );
	
	b_delete = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	sb_b->Add( b_delete, 0, wxALL, 5 );
	
	
	mainSizer->Add( sb_b, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( gui_v2capplication::OnCloseDialog ) );
	tc_processname->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( gui_v2capplication::Ontc_processname ), NULL, this );
	b_addaction->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2capplication::Onb_addaction ), NULL, this );
	b_addaction->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( gui_v2capplication::OnUpdateUI ), NULL, this );
	b_editaction->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2capplication::Onb_editaction ), NULL, this );
	b_save->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2capplication::Onb_save ), NULL, this );
	b_cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2capplication::Onb_cancel ), NULL, this );
	b_delete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2capplication::Onb_delete ), NULL, this );
}

gui_v2capplication::~gui_v2capplication()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( gui_v2capplication::OnCloseDialog ) );
	tc_processname->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( gui_v2capplication::Ontc_processname ), NULL, this );
	b_addaction->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2capplication::Onb_addaction ), NULL, this );
	b_addaction->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( gui_v2capplication::OnUpdateUI ), NULL, this );
	b_editaction->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2capplication::Onb_editaction ), NULL, this );
	b_save->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2capplication::Onb_save ), NULL, this );
	b_cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2capplication::Onb_cancel ), NULL, this );
	b_delete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui_v2capplication::Onb_delete ), NULL, this );
	
}
