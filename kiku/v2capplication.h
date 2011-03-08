/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/

#ifndef V2CAPPLICATION_H
#define V2CAPPLICATION_H

#include "gui_v2capplication.h"
#include <wx/wx.h>
#include <wx/valtext.h>
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

#include "v2ceditor.h"

class MainFrame;

class V2cApplication : public gui_v2capplication {

	public:
		V2cApplication(wxWindow *parent, wxString language);
		V2cApplication(wxWindow *parent, wxString language, wxString v2c);
		~V2cApplication();
		virtual void OnUpdateUI( wxUpdateUIEvent& event );
		virtual void OnCloseDialog( wxCloseEvent& event );
		virtual void Onb_save( wxCommandEvent& event );
		virtual void Onb_addaction( wxCommandEvent& event );
		virtual void Onb_editaction( wxCommandEvent& event );
		virtual void Onb_delete( wxCommandEvent& event );
		virtual void Ontc_processname( wxCommandEvent& event ); 		
		void reloadedit();
		
	private:
		MainFrame *mf;
		V2cEditor* dv2ceditor;
		
		void autocomplete();
		void autocompleteprocess();
		int IsNumeric(const char* ccharptr_CharacterList);
		bool save();
		
		wxArrayString v2a;
		wxString g_language;
		wxString v2afile;
		bool editmode;
		bool bugpn;
		
		// standard path
		wxStandardPaths stdpath;

};

const int TIMER_ID = 100000;

#endif // V2CAPPLICATION_H
