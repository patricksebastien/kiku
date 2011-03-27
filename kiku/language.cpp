/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#include "language.h"
#include "main.h"

bool Language::download(wxString server, wxString tgz)
{
	#ifdef DEBUG
		wxPuts("Start LanguageDownload");
	#endif

	// not in thread because: http://groups.google.com/group/wx-users/browse_thread/thread/a2ac8b947b657f78
	wxHTTP get;
	get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
	get.SetTimeout(10); 
	
	int tried = 0;
	while (!get.Connect(server)) {
		if(tried > 2) {
			return 0;
		}
		wxSleep(2);
		tried++;
	}
	
	wxInputStream *httpStream = get.GetInputStream(tgz);
	
	if (get.GetError() == wxPROTO_NOERR)
	{
		// standard path
		wxStandardPaths stdpath;
		stdpath = wxStandardPaths::Get();
		wxFileOutputStream outStream(stdpath.GetTempDir()+"/model.tar.gz");
		int ts = httpStream->GetSize();
		const int DLBUFSIZE = 4096;
		unsigned char buffer[DLBUFSIZE+1];
		do {
			static int bs = 0;
			httpStream->Read(buffer, DLBUFSIZE);
			size_t bytes_read = httpStream->LastRead();
			if (bytes_read > 0) {
				buffer[bytes_read] = 0;
				outStream.Write(buffer, bytes_read);
			}
			bs += bytes_read;
			mf_pHandler->OnLanguageProgess(bs, ts);
		} while ( !httpStream->Eof() );
		
		outStream.Close();
		
	} else {
		return 0;
	}
	#ifdef DEBUG
		wxPuts("Done LanguageDownload");
	#endif
	wxDELETE(httpStream);
	get.Close();
	
	return 1;
}


bool Language::gunzip(wxString file_target, wxString file_source)
{
	#ifdef DEBUG
		wxPuts("Start GUNZIP");
	#endif
	
	char buffer[1024];
	wxTempFile target(file_target);
	bool write = false;
	wxFileInputStream source(file_source);
	wxZlibInputStream inputStream(source);

	while (!inputStream.Eof()) {
			inputStream.Read(buffer, sizeof(buffer));
			if (inputStream.LastRead()) {
					target.Write(buffer, inputStream.LastRead());
			} else {
					break;
			}
	};
	write = inputStream.IsOk() || inputStream.Eof();

	if (write) {
			target.Commit();
	}
	#ifdef DEBUG
		wxPuts("Done GUNZIP");
	#endif
	
	return 1;
}

bool Language::untar(wxString file_source, wxString directory)
{
	#ifdef DEBUG
		wxPuts("Start UNTAR");
	#endif
    
	int i = 0;
    wxFFileInputStream inputStr(file_source);
    if (inputStr.Ok())
    {
        wxTarInputStream tarStr(inputStr);

        wxTarEntry* tarEntry = NULL;
        while (true)
        {
            if (tarEntry)
            {
                delete tarEntry;
            }
            tarEntry = tarStr.GetNextEntry();
            if (!tarEntry)
                break;
            else
            {
                if (tarEntry->GetTypeFlag() == wxTAR_REGTYPE)
                {
                    wxString tarFile = tarEntry->GetInternalName();
					
                    // Extract to destination
                    wxString destFilename = directory + tarFile;
                    tarStr.OpenEntry(*tarEntry);
                    wxString path = wxPathOnly(destFilename);

                    if (!wxDirExists(path)) {
						wxString p;
						wxStringTokenizer tkz(path, wxT("/\\"));
						p = tkz.GetNextToken();
						while (tkz.HasMoreTokens())
						{
							wxString token = tkz.GetNextToken();

							p += wxFILE_SEP_PATH + token;
							if (!wxDirExists(p))
							{
								if (!wxMkdir(p)) {
									wxPuts("problem creating dir");
									return 0;
								}
							}
						}
					}
					wxFileOutputStream outStream(destFilename);
					if (!outStream.Ok()) {
						return 0;
					}
					static unsigned char buf[1024];
					size_t bytesLeft = tarStr.GetSize();
					while (bytesLeft > 0)
					{
						size_t bytesToRead = wxMin((size_t) 1024, bytesLeft);
						tarStr.Read((void*) buf, bytesToRead);
						outStream.Write((void*) buf, bytesToRead);
						bytesLeft -= bytesToRead;
					}
					// chmod?
                }
                i ++;
            }
        }
    }
	#ifdef DEBUG
		wxPuts("Done UNTAR");
	#endif
	
	return 1;
}