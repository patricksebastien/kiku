/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#include "web.h"
#include "main.h"


void Web::ParseFile(wxString whaturl)
{
	
	if(whaturl == "/KIKU/packages.txt") {
		wxString packageName(wxT("MSW"));
		#if defined(__WXGTK__)
			packageName = wxT("GTK");
		#elif defined(__WXMAC__)
			packageName = wxT("MAC");
		#endif

		wxArrayString lines = wxStringTokenize(m_dataRead, wxT("\n"));
		for (size_t i=0; i<lines.GetCount(); i++) {
			wxString line = lines.Item(i);
			line = line.Trim().Trim(false);
			if (line.StartsWith(wxT("#"))) {
				//comment line
				continue;
			}

			// parse the line
			wxArrayString tokens = wxStringTokenize(line, wxT("|"));
			if (tokens.GetCount() > 3) {
				// find the entry with our package name
				if (tokens.Item(0).Trim().Trim(false) == packageName) {
					wxString url = tokens.Item(2).Trim().Trim(false);
					wxString rev = tokens.Item(1).Trim().Trim(false);
					wxString releaseNotesUrl = tokens.Item(3).Trim().Trim(false);

					long currev;
					long webrev(0);

					// convert strings to long
					wxString sCurRev(VERSION);
					sCurRev.ToLong(&currev);

					wxString sUrlRev(rev);
					sUrlRev.ToLong(&webrev);
					//wxMessageBox(rev);

					if ( webrev > currev ) {
						// notify the user that a new version is available
						//e.SetClientData(new WebJobData(url.c_str(), releaseNotesUrl.c_str(), currev, webrev, false, m_userRequest));
						wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, WEB_ID );
						event.SetString(url);
						wxGetApp().AddPendingEvent( event );
						//m_pHandler->OnWeb(url, releaseNotesUrl, currev, webrev);
					}
					break;
				}
			}
		}
	}
}

// thread
Web::ExitCode Web::Entry()
{
	#ifdef DEBUG
		fprintf(stdout, "Start Web\n");
	#endif

	wxHTTP get;
	get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
	get.SetTimeout(30); 
	 
	while (!get.Connect(_T("www.workinprogress.ca"))) {
		if(TestDestroy()) {
			return (wxThread::ExitCode)0;
		} else {
			wxSleep(5);
		}
	}
		
	wxInputStream *in_stream = get.GetInputStream(whaturl);
	
	if (get.GetError() == wxPROTO_NOERR)
	{
		bool shutdownRequest = false;
		unsigned char buffer[DLBUFSIZE+1];
		do {
			Sleep(0); //http://trac.wxwidgets.org/ticket/10720
			in_stream->Read(buffer, DLBUFSIZE);
			size_t bytes_read = in_stream->LastRead();
			if (bytes_read > 0) {

				buffer[bytes_read] = 0;
				wxString buffRead((const char*)buffer, wxConvUTF8);
				m_dataRead.Append(buffRead);
			}

			// Check termination request from time to time
			if(TestDestroy()) {
				shutdownRequest = true;
				break;
			}

		} while ( !in_stream->Eof() );
		
		wxDELETE(in_stream);
		get.Close();

		if(shutdownRequest == false) {
			delete in_stream;
			ParseFile(whaturl);
		}
		
	} else {
		return (wxThread::ExitCode)0;
	}
	#ifdef DEBUG
		fprintf(stdout, "Done Web\n");	
	#endif
	
	return (wxThread::ExitCode)0; // success
}

Web::~Web()
{
	wxCriticalSectionLocker enter(m_pHandler->m_pWebCS);
	m_pHandler->m_pWebThread = NULL;
}
