#ifndef WEB_H
#define WEB_H

#include <wx/wx.h>
#include <wx/thread.h>
#include <wx/url.h>
#include <wx/tokenzr.h>

class MainFrame; // forward declaration

// thread
class Web : public wxThread
{
    public:
        Web(MainFrame *handler, wxString what)
            : wxThread(wxTHREAD_DETACHED)
            { m_pHandler = handler; whaturl = what; }
        ~Web();

	protected:
        virtual ExitCode Entry();
        MainFrame *m_pHandler;
		
		void ParseFile(wxString whaturl);
		wxString m_dataRead;
		wxString whaturl;
};

#endif // WEB_H
