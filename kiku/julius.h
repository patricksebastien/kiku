/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#ifndef JULIUS_H
#define JULIUS_H

#include <julius/juliuslib.h>

#include <wx/filename.h>
#include <wx/file.h>
#include <wx/wfstream.h>

#include <wx/dir.h>
#include <wx/stdpaths.h>
#include <wx/regex.h>
#include <wx/txtstrm.h>
#include <wx/textfile.h>
#include <wx/regex.h>
#include <wx/process.h>

// julius callback
void callback_engine_pause_func(Recog *recog, void *dummy);
void callback_engine_pause(Recog *recog, void *dummy);
void callback_engine_resume(Recog *recog, void *dummy);
void status_recready(Recog *recog, void *dummy);
void status_recstart(Recog *recog, void *dummy);
void status_recstop(Recog *recog, void *dummy);
void output_result(Recog *recog, void *dummy);
void status_recognition_begin(Recog *recog, void *dummy);
void status_recognition_end(Recog *recog, void *dummy);
void levelmeter(Recog *recog, SP16 *buf, int len, void *dummy);

// forward declaration
class MainFrame;

class Julius {

	public:
		Julius(MainFrame* mf) { mf_pHandler = mf; stdpath = wxStandardPaths::Get(); }
        bool start_recognition();
		void pause_recognition();
		void resume_recognition();
		bool stop_recognition();
		bool update_grammar();

	private:
		MainFrame *mf_pHandler;
		void openLogFile();
        bool loadConfigFile();
		void addCallbacks();
        Jconf *jconf;
        Recog *recog;
		FILE *srm_log_fp;
		
		// standard path
		wxStandardPaths stdpath;
};



#endif // JULIUS_H
