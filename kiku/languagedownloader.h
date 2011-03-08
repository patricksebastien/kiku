/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#ifndef LANGUAGEDOWNLOADER_H
#define LANGUAGEDOWNLOADER_H

#include <wx/thread.h>
#include <wx/sstream.h>
#include <wx/protocol/http.h>
#include <wx/socket.h>

class MainFrame; // forward declaration

// thread
class LanguageDownloader : public wxThread
{
    public:
        LanguageDownloader(MainFrame *handler)
            : wxThread(wxTHREAD_DETACHED)
            { m_pHandler = handler; }
        ~LanguageDownloader();

	protected:
        virtual ExitCode Entry();
        MainFrame *m_pHandler;
};


#endif // LANGUAGEDOWNLOADER_H
