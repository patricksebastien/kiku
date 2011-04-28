/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 * mf_pHandler->testing("fdfsd");
 *********************************************************************/
 
#include "julius.h"
#include "main.h"

extern bool paused;
extern bool juliusisready;
wxStopWatch watch;

void status_recready(Recog *recog, void *dummy)
{
	if (recog->jconf->input.speech_input == SP_MIC || recog->jconf->input.speech_input == SP_NETAUDIO) {
        if(paused) {
            wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, READY_ID );
            event.SetString("Paused.");
            wxGetApp().AddPendingEvent( event );
        } else {
			wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, READY_ID );
			event.SetString("You can now speak.");
			wxGetApp().AddPendingEvent( event );
        }
	}
}

void status_recstart(Recog *recog, void *dummy)
{
	if(paused) {
		wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, READY_ID );
		event.SetString("Paused.");
		wxGetApp().AddPendingEvent( event );
	} else {
		wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, READY_ID );
		event.SetString("Listening...");
		wxGetApp().AddPendingEvent( event );
	}

	//Start the watch for the duration
	watch.Start();
}

void status_recstop(Recog *recog, void *dummy)
{
	if(!paused) {
		wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, WATCH_ID );
		event.SetInt(watch.Time());
		wxGetApp().AddPendingEvent( event );
	}
}

void callback_engine_pause_func(Recog *recog, void *dummy)
{
    usleep(1);
}

/*
void levelmeter(Recog *recog, SP16 *buf, int len, void *dummy)
{
	float d;
    int level, i;

    level = 0;
    for(i=0;i<len;i++) {
        if (level < buf[i]) level = buf[i];
    }

    d = log((float)(level+1)) / 10.3971466;
	d = d * 32767.0;

    wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, LEVELMETER_ID );
    event.SetInt((int)d);
    wxGetApp().AddPendingEvent( event );
}
*/

void put_hypo_phoneme(WORD_ID *seq, int n, WORD_INFO *winfo)
{
	int i,j;
	WORD_ID w;
	static char buf[MAX_HMMNAME_LEN];

	if (seq != NULL) {
		for (i=0;i<n;i++) {
			if (i > 0) {
			    //printf(" |");

                wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, PRONUN_ID );
                event.SetString("-");
                wxGetApp().AddPendingEvent( event );

            }

			w = seq[i];
			for (j=0;j<winfo->wlen[w];j++) {
				center_name(winfo->wseq[w][j]->name, buf);

                wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, PRONUN_ID );
                event.SetString(buf);
                wxGetApp().AddPendingEvent( event );

				//printf(" %s", buf);
			}
		}
	}
	wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, PRONUN_ID );
    event.SetString("\n");
    wxGetApp().AddPendingEvent( event );

    //printf("\n");
}

void output_result(Recog *recog, void *dummy)
{
	int i;
	WORD_INFO *winfo;
	WORD_ID *seq;
	int seqnum;
	int n;
	Sentence *s;
	RecogProcess *r;
	HMM_Logical *p;
	SentenceAlign *align;

	/* all recognition results are stored at each recognition proces instance */
	for(r=recog->process_list;r;r=r->next) {

		/* skip the process if the process is not alive */
		if (! r->live) continue;

		/* result are in r->result.  See recog.h for details */

		/* check result status */
		if (r->result.status < 0) {      /* no results obtained */

			/* outout message according to the status code */
			switch(r->result.status) {
				case J_RESULT_STATUS_REJECT_POWER:
					//printf("<input rejected by power>\n");
					break;
				case J_RESULT_STATUS_TERMINATE:
					//printf("<input teminated by request>\n");
					break;
				case J_RESULT_STATUS_ONLY_SILENCE:
					//printf("<input rejected by decoder (silence input result)>\n");
					break;
				case J_RESULT_STATUS_REJECT_GMM:
					//printf("<input rejected by GMM>\n");
					break;
				case J_RESULT_STATUS_REJECT_SHORT:
					//printf("<input rejected by short input>\n");
					break;
				case J_RESULT_STATUS_FAIL:
					//printf("<search failed>\n");
					break;
			}
			/* continue to next process instance */
			continue;
		}

		/* output results for all the obtained sentences */
		winfo = r->lm->winfo;

		for(n = 0; n < r->result.sentnum; n++) { /* for all sentences */

			s = &(r->result.sent[n]);
			seq = s->word;
			seqnum = s->word_num;





			/* LM entry sequence */
			//printf("wseq%d:", n+1);
			for(i=0;i<seqnum;i++) {
				//printf(" %s", winfo->wname[seq[i]]);
			}
			//printf("\n");
			/* phoneme sequence */
			//printf("phseq%d:", n+1);
			put_hypo_phoneme(seq, seqnum, winfo);
			//printf("\n");


			/* confidence scores */
			//printf("cmscore%d:", n+1);
			for (i=0;i<seqnum; i++) {

                wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, SCORE_ID );
                event.SetString(wxString::Format("%f", s->confidence[i]));
                wxGetApp().AddPendingEvent( event );

			    //printf(" %5.3f", s->confidence[i]);
			}
			//printf("\n");



			/* output word sequence like Julius */
			//printf("sentence%d:", n+1);
			for(i=0;i<seqnum;i++) {
			     //printf(" %s", winfo->woutput[seq[i]]);

			     wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, SENTENCE_ID );
                 event.SetString(winfo->woutput[seq[i]]);
                 wxGetApp().AddPendingEvent( event );
			}
			/*
			wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, SENTENCE_ID );
            event.SetString("\n");
            wxGetApp().AddPendingEvent( event );
            */
			//printf("\n");


			/* AM and LM scores */
			//printf("score%d: %f", n+1, s->score);
			if (r->lmtype == LM_PROB) { /* if this process uses N-gram */
				//printf(" (AM: %f  LM: %f)", s->score_am, s->score_lm);
			}
			//printf("\n");
			if (r->lmtype == LM_DFA) { /* if this process uses DFA grammar */
				/* output which grammar the hypothesis belongs to
				 when using multiple grammars */
				if (multigram_get_all_num(r->lm) > 1) {
					//printf("grammar%d: %d\n", n+1, s->gram_id);
				}
			}

			/* output alignment result if exist */
			for (align = s->align; align; align = align->next) {
				//printf("=== begin forced alignment ===\n");
				/*
				switch(align->unittype) {
					case PER_WORD:
						//printf("-- word alignment --\n"); break;
					case PER_PHONEME:
						//printf("-- phoneme alignment --\n"); break;
					case PER_STATE:
						//printf("-- state alignment --\n"); break;
				}
				*/
				//printf(" id: from  to    n_score    unit\n");
				//printf(" ----------------------------------------\n");
				for(i=0;i<align->num;i++) {
					//printf("[%4d %4d]  %f  ", align->begin_frame[i], align->end_frame[i], align->avgscore[i]);
					switch(align->unittype) {
						case PER_WORD:
							//printf("%s\t[%s]\n", winfo->wname[align->w[i]], winfo->woutput[align->w[i]]);
							break;
						case PER_PHONEME:
							p = align->ph[i];
							if (p->is_pseudo) {
								//printf("{%s}\n", p->name);
							} else if (strmatch(p->name, p->body.defined->name)) {
								//printf("%s\n", p->name);
							} else {
								//printf("%s[%s]\n", p->name, p->body.defined->name);
							}
							break;
						case PER_STATE:
							p = align->ph[i];
							if (p->is_pseudo) {
								//printf("{%s}", p->name);
							} else if (strmatch(p->name, p->body.defined->name)) {
								//printf("%s", p->name);
							} else {
								//printf("%s[%s]", p->name, p->body.defined->name);
							}
							if (r->am->hmminfo->multipath) {
								if (align->is_iwsp[i]) {
									//printf(" #%d (sp)\n", align->loc[i]);
								} else {
									//printf(" #%d\n", align->loc[i]);
								}
							} else {
								//printf(" #%d\n", align->loc[i]);
							}
							break;
					}
				}

				//printf("re-computed AM score: %f\n", align->allscore);

				//printf("=== end forced alignment ===\n");
			}
		}
	}

	/* flush output buffer */
	fflush(stdout);
}


bool Julius::start_recognition()
{
	#ifdef DEBUG
		openLogFile();
	#endif
	
	#ifndef DEBUG
		jlog_set_output(NULL);
	#endif
	
	loadConfigFile();
	addCallbacks();
	
	if (j_adin_init(recog) == FALSE) {
		fprintf(stderr, "error in j_adin_init\n");
		return false;
	}

	//will output julius info to log
	#ifdef DEBUG
		j_recog_info(recog);
		fflush(srm_log_fp);
	#endif

	switch(j_open_stream(recog, NULL)) {
		case 0:
			//fprintf(stderr, "ok j_open_stream");
			break;
		case -1:
			fprintf(stderr, "error in input stream");
			return false;
		case -2:
			fprintf(stderr, "error in beginning input");
			return false;
	}

	// infinite loop - until j_close_stream is call
	juliusisready = true;
	int ret = j_recognize_stream(recog);

	if (ret == -1) {
		// when use a plugin it complain but works... so commented
		//fprintf(stderr, "error j_recognize_stream");
		return false;
	}
	#ifdef DEBUG
		wxPuts("out of j_recognize_stream()");
	#endif
	
	// clean
	j_recog_free(recog);
    recog = NULL;
    jconf = NULL;
	
	#ifdef DEBUG
		fclose(srm_log_fp);
		srm_log_fp = NULL;
	#endif

	return true;
}

void Julius::openLogFile()
{
	srm_log_fp = fopen("log.txt", "w");
	//jlog_set_output(srm_log_fp);
}

bool Julius::loadConfigFile()
{
	
	wxString conf(stdpath.GetUserDataDir()+"/language/julius.conf");
	
	jconf = j_config_load_file_new(const_cast<char*>( (const char*)conf.mb_str() ));
	
	if (jconf == NULL) {
		fprintf(stderr, "error in j_config_load_file_new\n");
		return false;
	}

	recog = j_create_instance_from_jconf(jconf);
	if (recog == NULL) {
		wxStandardPaths stdpath;
		wxRemoveFile(stdpath.GetUserDataDir()+"/language/julius.conf");
		wxRemoveFile(stdpath.GetUserDataDir()+"/language/dictionary");
		fprintf(stderr, "error in j_create_instance_from_jconf\n");
		return false;
	}
	
	return true;
}


void Julius::addCallbacks()
{
	::callback_add(recog, CALLBACK_EVENT_SPEECH_READY, status_recready, NULL);
	::callback_add(recog, CALLBACK_EVENT_SPEECH_START, status_recstart, NULL);
	::callback_add(recog, CALLBACK_EVENT_SPEECH_STOP, status_recstop, NULL);
	::callback_add(recog, CALLBACK_RESULT, output_result, NULL);
    ::callback_add(recog, CALLBACK_PAUSE_FUNCTION, callback_engine_pause_func, NULL);    
    //::callback_add_adin(recog, CALLBACK_ADIN_CAPTURED, levelmeter, NULL);
	
    /*
	::callback_add(recog, CALLBACK_EVENT_RECOGNITION_BEGIN, status_recognition_begin, NULL);
    ::callback_add(recog, CALLBACK_EVENT_RECOGNITION_END, status_recognition_end, NULL);
	::callback_add_adin(recog, CALLBACK_ADIN_TRIGGERED, record_sample_write, NULL);
    ::callback_add(recog, CALLBACK_EVENT_PAUSE, callback_engine_pause, NULL);
    ::callback_add(recog, CALLBACK_EVENT_RESUME, callback_engine_resume, NULL);
    ::callback_add(recog, CALLBACK_EVENT_PROCESS_ONLINE, status_process_online, data);
    ::callback_add(recog, CALLBACK_EVENT_PROCESS_OFFLINE, status_process_offline, data);
    ::callback_add(recog, CALLBACK_EVENT_SPEECH_STOP, status_recend, data);
    ::callback_add(recog, CALLBACK_EVENT_RECOGNITION_BEGIN, status_recognition_begin, data);
    ::callback_add(recog, CALLBACK_EVENT_RECOGNITION_END, status_recognition_end, data);
    */
}

bool Julius::stop_recognition()
{
	j_close_stream(recog);
	return 1;
}

void Julius::pause_recognition()
{
    j_request_terminate(recog);
    j_request_pause(recog);
}

void Julius::resume_recognition()
{
    j_request_resume(recog);
}
