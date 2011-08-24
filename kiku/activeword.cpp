/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#include "activeword.h"
#include "main.h"

int wxCALLBACK MyCompareFunction(wxIntPtr item1, wxIntPtr item2, wxIntPtr WXUNUSED(sortData))
{
	extern wxArrayString trigger;
	wxString a, b;
	a = trigger.Item(item1);
	b = trigger.Item(item2);
	return a.CmpNoCase(b);
}

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
	listctrl_shortcut->InsertColumn(0, "Trigger");
	listctrl_shortcut->InsertColumn(1, "Pre-trigger");
	listctrl_shortcut->InsertColumn(2, "Command");
	listctrl_shortcut->InsertColumn(3, "Comment");
	listctrl_shortcut->SetColumnWidth( 0, WIDTH );
    listctrl_shortcut->SetColumnWidth( 1, WIDTH );
    listctrl_shortcut->SetColumnWidth( 2, WIDTH );
	listctrl_shortcut->SetColumnWidth( 3, WIDTH );
	
	// application
	listctrl_app->InsertColumn(0, "Trigger");
	listctrl_app->InsertColumn(1, "Pre-trigger");
	listctrl_app->InsertColumn(2, "ProcessName");
	listctrl_app->InsertColumn(3, "Comment");
	listctrl_app->SetColumnWidth( 0, WIDTH );
    listctrl_app->SetColumnWidth( 1, WIDTH );
    listctrl_app->SetColumnWidth( 2, WIDTH );
	listctrl_app->SetColumnWidth( 3, WIDTH );
	
	// launcher
	listctrl_launcher->InsertColumn(0, "Trigger");
	listctrl_launcher->InsertColumn(1, "Pre-trigger");
	listctrl_launcher->InsertColumn(2, "ProcessName");
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
	extern wxArrayString comment;
	extern wxArrayString process;
	extern wxArrayString v2c;
	
	// shortcut
	listctrl_shortcut->Hide();
    for (unsigned int i = 0; i < trigger.GetCount(); i++ )
    {
		if(v2c.Item(i) == "v2s") {
			long tmp = listctrl_shortcut->InsertItem(listctrl_shortcut->GetItemCount(), trigger.Item(i).Lower(), 0);
			listctrl_shortcut->SetItem(tmp, 1, pretrigger.Item(i).Lower());
			listctrl_shortcut->SetItem(tmp, 2, command.Item(i).Lower());
			listctrl_shortcut->SetItem(tmp, 3, comment.Item(i).Lower());
		}
    }
    listctrl_shortcut->Show();
	
	// application
    listctrl_app->Hide();
    for (unsigned int i = 0; i < trigger.GetCount(); i++ )
    {
		if(v2c.Item(i) == "v2a") {
			long tmp = listctrl_app->InsertItem(listctrl_app->GetItemCount(), trigger.Item(i).Lower(), 0);
			listctrl_app->SetItemData(tmp, i);
			listctrl_app->SetItem(tmp, 1, pretrigger.Item(i).Lower());
			listctrl_app->SetItem(tmp, 2, process.Item(i).Lower());
			listctrl_app->SetItem(tmp, 3, comment.Item(i).Lower());
		}
    }
    listctrl_app->Show();
	listctrl_app->SortItems(MyCompareFunction, 0);

	// launcher
    listctrl_launcher->Hide();
    for (unsigned int i = 0; i < trigger.GetCount(); i++ )
    {
		if(v2c.Item(i) == "launcher") {
			
			if(command.Item(i).Lower() != "null") {
				long tmp = listctrl_launcher->InsertItem(listctrl_launcher->GetItemCount(), trigger.Item(i).Lower(), 0);
				listctrl_launcher->SetItem(tmp, 1, pretrigger.Item(i).Lower());
				listctrl_launcher->SetItem(tmp, 2, command.Item(i).Lower());
			}
		}
    }
    listctrl_launcher->Show();
}