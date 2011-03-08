///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov 18 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui_activeword__
#define __gui_activeword__

#include <wx/intl.h>

#include <wx/listctrl.h>
#include <wx/string.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/notebook.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class gui_activeword
///////////////////////////////////////////////////////////////////////////////
class gui_activeword : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* m_notebook1;
		wxPanel* m_panel3;
		wxListCtrl* listctrl_launcher;
		wxButton* b_applicationrefresh11;
		wxPanel* m_panel1;
		wxListCtrl* listctrl_app;
		wxButton* b_applicationrefresh;
		wxPanel* m_panel2;
		wxListCtrl* listctrl_shortcut;
		wxButton* b_applicationrefresh1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void Onb_applicationrefresh( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		gui_activeword( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Active word"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,480 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~gui_activeword();
	
};

#endif //__gui_activeword__
