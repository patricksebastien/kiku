/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <wx/wx.h>
#include <wx/stdpaths.h>

// forward declaration
class MainFrame;

class Language {

	public:
		Language(MainFrame* mf) { mf_pHandler = mf; }
		bool download(wxString, wxString);
		bool gunzip(wxString, wxString);
		bool untar(wxString, wxString);
	
	private:
		MainFrame *mf_pHandler;
	
};

#endif // LANGUAGE_H
