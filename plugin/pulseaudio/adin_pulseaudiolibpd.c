/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../common/plugin_defs.h"

// libpd
#include "../../common/z_libpd.h"

// pulseaudio
#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>

#define BUFSIZE 512
#define SAMPLE_RATE 16000
#define NBCHANNEL 1

#define PLUGIN_TITLE "PulseAudio & libpd A/D-in plugin for Julius"
#define INPUT_OPT "pulseaudio-libpd"

int
initialize()
{
	return 0;
}

int
get_plugin_info(int opcode, char *buf, int buflen)
{
	switch(opcode) {
	case 0:
	/* plugin description string */
	strncpy(buf, PLUGIN_TITLE, buflen);
	break;
	}

	return 0;
}

void
adin_get_optname(char *buf, int buflen)
{
	strncpy(buf, INPUT_OPT, buflen);
}

int
adin_get_configuration(int opcode)
{
	/* typical values for live microphone/line input */
	switch(opcode) {
	case 0:	
	return 1;
	case 1:
	return 1;
	case 2:
	return 1;
	}
}

pa_simple *r = NULL;
int errorpa;

boolean
adin_standby(int sfreq, void *dummy)
{	
	static const pa_sample_spec ss = {
		.format = PA_SAMPLE_S16LE,
		.rate = SAMPLE_RATE,
		.channels = NBCHANNEL,
	};
	
	// low-latency setting
	pa_buffer_attr ba;
	ba.tlength = pa_usec_to_bytes(50*1000, &ss);
	ba.minreq = pa_usec_to_bytes(0, &ss);
	ba.maxlength = pa_usec_to_bytes(50*1000, &ss);
	ba.fragsize = sizeof(uint32_t) -1;
	
	// input
	if (!(r = pa_simple_new(NULL, "kiku", PA_STREAM_RECORD, NULL, "voice recognition", &ss, NULL, &ba, &errorpa))) {
		return FALSE;
	}
	
  return TRUE;
}
 
boolean
adin_open(char *pathname)
{
	return(TRUE);
}

int
adin_read(SP16 * buf, int sampnum)
{	
	int cnt, bufsize;
	bufsize = sampnum * sizeof(SP16);
	
	if (bufsize > BUFSIZE) bufsize = BUFSIZE;
	
	SP16 inbuf[bufsize];
	
	
	if (pa_simple_read(r, inbuf, bufsize, &errorpa) < 0) {
		printf("Error: adin_pulseaudio: pa_simple_read() failed: %s\n", pa_strerror(errorpa));
		return (-2);
	}
	
	libpd_process_short(inbuf, buf);

	cnt = bufsize / sizeof(SP16);
	return(cnt);
}

boolean
adin_close()
{
	if(r) {
		pa_simple_free(r);
		r = NULL;
	}
	return TRUE;
}

boolean
adin_terminate()
{	
  //printf("terminate request\n");
  return TRUE;
}

boolean
adin_pause()
{
  //printf("pause request\n");
  return TRUE;
}

boolean
adin_resume()
{
  //printf("resume request\n");
  return TRUE;
}

char *
adin_input_name()
{
  printf("input name function was called\n");
  return("default");
}
