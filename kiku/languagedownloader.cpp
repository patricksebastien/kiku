/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 

LanguageDownloader::ExitCode LanguageDownloader::Entry()
{
	#ifdef DEBUG
		fprintf(stdout, "Start LanguageDownloader\n");
	#endif
	
	wxHTTP get;
	get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
	get.SetTimeout(5); 
	while (!get.Connect(_T("www.workinprogress.ca")))
		wxSleep(5);
	 
	wxInputStream *httpStream = get.GetInputStream(_T("/index.php"));
	
	if (get.GetError() == wxPROTO_NOERR)
	{
		wxFileOutputStream outStream("nihonsaikosss.mp3");
		
		const int DLBUFSIZE = 4096;
		unsigned char buffer[DLBUFSIZE+1];
		do {
			httpStream->Read(buffer, DLBUFSIZE);
			size_t bytes_read = httpStream->LastRead();
			if (bytes_read > 0) {
				buffer[bytes_read] = 0;
				outStream.Write(buffer, bytes_read);
			}
			// for gauge
			wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, LDUP_ID );
            event.SetInt(1);
            wxGetApp().AddPendingEvent( event );
		} while ( !httpStream->Eof() );
		
		outStream.Close();
	}
	else
	{
		wxMessageBox(_T("Unable to connect!"));
	}
	 
	wxDELETE(httpStream);
	get.Close();
	
	#ifdef DEBUG
		fprintf(stdout, "Done LanguageDownloader\n");	
	#endif
	
	// for gauge
	wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, LDEND_ID );
	event.SetInt(1);
	wxGetApp().AddPendingEvent( event );
	
	return (wxThread::ExitCode)0; // success
}

LanguageDownloader::~LanguageDownloader()
{
	wxCriticalSectionLocker enter(m_pHandler->m_pLanguageDownloaderCS);
	m_pHandler->m_pLanguageDownloaderThread = NULL;
}