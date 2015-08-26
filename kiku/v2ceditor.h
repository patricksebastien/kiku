/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#ifndef V2CEDITOR_H
#define V2CEDITOR_H

#include <wx/wx.h>
#include <wx/file.h>
#include <wx/arrstr.h>
#include <wx/textentry.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/stdpaths.h>

// json
#include "jsonval.h"
#include "jsonreader.h"
#include "jsonwriter.h"

#include "gui_v2ceditor.h"

class V2cApplication;
class MainFrame;

class V2cEditor : public gui_v2ceditor {
	
	public:
		V2cEditor(wxWindow *parent, wxString language, wxString v2a, V2cApplication *myparent);
		V2cEditor(MainFrame *parent, wxString language, wxString v2a);
		V2cEditor(wxWindow *parent, wxString language, wxString v2a, V2cApplication *myparent, wxString edit);
		V2cEditor(MainFrame *parent, wxString language, wxString v2a, wxString edit);
		~V2cEditor();
		virtual void Onb_add( wxCommandEvent& event );
		virtual void Onb_delete( wxCommandEvent& event );
		virtual void Onb_cancel( wxCommandEvent& event );
		
private:
		V2cApplication *theparent;
		MainFrame *themf;
		wxString g_language;
		wxString g_v2a;
		void autocomplete();
		bool save();
		bool editmode;
		wxString m_edit;
		
		// standard path
		wxStandardPathsBase& stdpath = wxStandardPaths::Get();
		
		void OnLink( wxHtmlLinkEvent& event );
};

#endif // V2CEDITOR_H
