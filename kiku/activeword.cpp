/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#include "activeword.h"
#include "main.h"

ActiveWord::ActiveWord( wxWindow* parent ) : gui_activeword( parent )
{
	m_parent = (MainFrame *)parent;
	initlist();
	fetchactions();
	
	// keyboard shortcut - F5
	const int rid = wxNewId();
	Connect(rid,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ActiveWord::Onb_applicationrefresh);
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_NORMAL, WXK_F5, rid);
    wxAcceleratorTable accel(1, entries);
    ActiveWord::SetAcceleratorTable(accel);
}

ActiveWord::~ActiveWord()
{
}

void ActiveWord::initlist()
{	
	// shortcut
	listctrl_shortcut->InsertColumn(0, "Command");
	listctrl_shortcut->InsertColumn(1, "Pre-trigger");
	listctrl_shortcut->InsertColumn(2, "Trigger");
	listctrl_shortcut->SetColumnWidth( 0, WIDTH );
    listctrl_shortcut->SetColumnWidth( 1, WIDTH );
    listctrl_shortcut->SetColumnWidth( 2, WIDTH );
	
	// application
	listctrl_app->InsertColumn(0, "ProcessName");
	listctrl_app->InsertColumn(1, "Pre-trigger");
	listctrl_app->InsertColumn(2, "Trigger");
	listctrl_app->SetColumnWidth( 0, WIDTH );
    listctrl_app->SetColumnWidth( 1, WIDTH );
    listctrl_app->SetColumnWidth( 2, WIDTH );
	
	// launcher
	listctrl_launcher->InsertColumn(0, "ProcessName");
	listctrl_launcher->InsertColumn(1, "Pre-trigger");
	listctrl_launcher->InsertColumn(2, "Trigger");
	listctrl_launcher->SetColumnWidth( 0, WIDTH );
    listctrl_launcher->SetColumnWidth( 1, WIDTH );
    listctrl_launcher->SetColumnWidth( 2, WIDTH );
}

void ActiveWord::Onb_applicationrefresh( wxCommandEvent& event )
{
	//m_parent->v2cloading();
	listctrl_app->ClearAll();
	listctrl_shortcut->ClearAll();
	listctrl_launcher->ClearAll();
	initlist();
	fetchactions();
}

void ActiveWord::fetchactions()
{	
	extern wxArrayString trigger;
	extern wxArrayString pretrigger;
	extern wxArrayString command;
	extern wxArrayString process;
	extern wxArrayString v2c;
	
	// shortcut
	listctrl_shortcut->Hide();
    for (unsigned int i = 0; i < trigger.GetCount(); i++ )
    {
		if(v2c.Item(i) == "v2s") {
			listctrl_shortcut->InsertItem(0, ""); // bad
			listctrl_shortcut->SetItem(0, 0, command.Item(i).Lower());
			listctrl_shortcut->SetItem(0, 1, pretrigger.Item(i).Lower());
			listctrl_shortcut->SetItem(0, 2, trigger.Item(i).Lower());
		}
    }
    listctrl_shortcut->Show();
	
	
	// application
    listctrl_app->Hide();
    for (unsigned int i = 0; i < trigger.GetCount(); i++ )
    {
		if(v2c.Item(i) == "v2a") {
			listctrl_app->InsertItem(0, ""); // bad
			listctrl_app->SetItem(0, 0, process.Item(i).Lower());
			listctrl_app->SetItem(0, 1, pretrigger.Item(i).Lower());
			listctrl_app->SetItem(0, 2, trigger.Item(i).Lower());
		}
    }
    listctrl_app->Show();
	
	// launcher
    listctrl_launcher->Hide();
    for (unsigned int i = 0; i < trigger.GetCount(); i++ )
    {
		if(v2c.Item(i) == "launcher") {
			listctrl_launcher->InsertItem(0, ""); // bad
			listctrl_launcher->SetItem(0, 0, command.Item(i).Lower());
			listctrl_launcher->SetItem(0, 1, pretrigger.Item(i).Lower());
			listctrl_launcher->SetItem(0, 2, trigger.Item(i).Lower());
		}
    }
    listctrl_launcher->Show();
}