/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 * 
 * the more the buffer is small the more cpu...
 *********************************************************************/
 
//`pkg-config --cflags --libs libpulse-simple`

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plugin_defs.h"

#define PLUGIN_TITLE "PulseAudio & libpd A/D-in plugin for Julius"
#define INPUT_OPT "pulseaudio-libpd"

boolean closed = 0;

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

// libpd
#include "z_libpd.h"

// pulseaudio
#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>

#define SAMPLE_RATE 16000
#define NBCHANNEL 1
#define BLOCKSIZE 64
#define TICK 3


pa_simple *r = NULL;
pa_simple *s = NULL;
int errorpa;

//libpd catch [print] function
void pdprint(const char *s) {
	printf("%s", s);
}


boolean
adin_standby(int sfreq, void *dummy)
{	
	libpd_printhook = (t_libpd_printhook) pdprint;
	libpd_init();
	libpd_init_audio(NBCHANNEL, NBCHANNEL, SAMPLE_RATE, TICK); // input channel, output channel, sr, one tick per buffer (blocksize 64)

	// compute audio    [; pd dsp 1(
	libpd_start_message();
	libpd_add_float(1.0f);
	libpd_finish_message("pd", "dsp");

	// open patch       [; pd open file folder(
	libpd_start_message();
	libpd_add_symbol("julius.pd");
	libpd_add_symbol("./plugin");
	libpd_finish_message("pd", "open");
	
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
	if (!(r = pa_simple_new(NULL, "julius", PA_STREAM_RECORD, NULL, "pa", &ss, NULL, &ba, &errorpa))) {
		return FALSE;
	}

	// output
	if (!(s = pa_simple_new(NULL, "julius", PA_STREAM_PLAYBACK, NULL, "pa", &ss, NULL, &ba, &errorpa))) {
		return FALSE;
	}
	
  return TRUE;
}
 
boolean
adin_open(char *pathname)
{
  return(TRUE);
}

SP16 inbuf[NBCHANNEL * BLOCKSIZE * TICK];

int
adin_read(SP16 * buf, int sampnum)
{	
	if(!closed) {
		// pulseaudio input
		pa_simple_read(r, inbuf, sizeof(SP16) * BLOCKSIZE * NBCHANNEL * TICK, &errorpa);

		// libpd process dsp
		libpd_process_short(inbuf, buf);
		
		// pulseaudio output
		pa_simple_write(s, buf, sizeof(SP16) * BLOCKSIZE * NBCHANNEL * TICK, &errorpa);
		return(sizeof(SP16) * BLOCKSIZE * NBCHANNEL * TICK);
	} else {
		printf("adin_read closed");
		return 0;
	}
}

boolean
adin_close()
{
	if(!closed) {
		printf("-adin_close CLOSIIIIIIIIIIINGGGg\n");
		  if(r) { pa_simple_free(r); }
		  closed = TRUE;
	}
	return FALSE;
}

boolean
adin_terminate()
{	
	
  printf("-why-terminate request\n");
  return TRUE;
}

boolean
adin_pause()
{
  printf("pause request\n");
  return TRUE;
}

boolean
adin_resume()
{
  printf("resume request\n");
  return TRUE;
}

char *
adin_input_name()
{
  printf("input name function was called\n");
  return("default");
}
