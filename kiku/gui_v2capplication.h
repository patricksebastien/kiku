///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov 18 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui_v2capplication__
#define __gui_v2capplication__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/choice.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class gui_v2capplication
///////////////////////////////////////////////////////////////////////////////
class gui_v2capplication : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* st_processname;
		wxTextCtrl* tc_processname;
		wxButton* b_addaction;
		wxChoice* c_editaction;
		wxButton* b_editaction;
		wxStaticText* m_staticText4;
		wxTextCtrl* tc_notification;
		wxStaticText* m_staticText5;
		wxTextCtrl* tc_pretrig;
		wxStaticText* m_staticText6;
		wxTextCtrl* tc_trig;
		wxStaticText* m_staticText8;
		wxTextCtrl* tc_command;
		wxButton* b_save;
		
		wxButton* b_delete;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ) { event.Skip(); }
		virtual void Ontc_processname( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onb_addaction( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void Onb_editaction( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onb_save( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onb_delete( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxString processnameval; 
		
		gui_v2capplication( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Application"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~gui_v2capplication();
	
};

#endif //__gui_v2capplication__
