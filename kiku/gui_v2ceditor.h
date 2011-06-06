///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 11 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui_v2ceditor__
#define __gui_v2ceditor__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/html/htmlwin.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class gui_v2ceditor
///////////////////////////////////////////////////////////////////////////////
class gui_v2ceditor : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText6;
		wxTextCtrl* tc_notification;
		wxStaticText* m_staticText7;
		wxTextCtrl* tc_pretrig;
		wxStaticText* m_staticText8;
		wxTextCtrl* tc_trig;
		wxStaticText* m_staticText9;
		wxTextCtrl* tc_command;
		wxStaticText* m_staticText10;
		wxChoice* c_type;
		
		wxStaticLine* m_staticline1;
		wxButton* b_add;
		wxButton* b_delete;
		wxHtmlWindow* html_v2ceditor;
		
		// Virtual event handlers, overide them in your derived class
		virtual void Onb_add( wxCommandEvent& event ) { event.Skip(); }
		virtual void Onb_delete( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		gui_v2ceditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("V2C editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,300 ), long style = wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER ); 
		~gui_v2ceditor();
	
};

#endif //__gui_v2ceditor__
