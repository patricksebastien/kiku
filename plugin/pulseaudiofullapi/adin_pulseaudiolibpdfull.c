#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <pulse/pulseaudio.h>
#include "../../common/plugin_defs.h"

#define PLUGIN_TITLE "PulseAudio full API A/D-in plugin for Julius"
#define INPUT_OPT "pulseaudio-fullapi"

#define BUFSIZE 512
#define SAMPLE_RATE 16000
#define NBCHANNEL 1

static pa_context *context = NULL;
static pa_stream *stream = NULL;
static pa_threaded_mainloop* mainloop = NULL;
static pa_mainloop_api *mainloop_api = NULL;
static char *stream_name = NULL;
static char *client_name = NULL;
static char *device = NULL;

static const pa_sample_spec sample_spec = {
    .format = PA_SAMPLE_S16LE,
    .rate = SAMPLE_RATE,
    .channels = NBCHANNEL
};

static pa_stream_flags_t flags = 0;
static pa_channel_map channel_map;
static int channel_map_set = 0;

static size_t buffer_index = 0;

/* A shortcut for terminating the application */
static void quit( int ret ) {
	assert( mainloop_api );
	mainloop_api->quit(mainloop_api, ret);
	pa_context_unref(context);
	pa_threaded_mainloop_stop(mainloop);
}

static void get_source_info_callback( pa_context *c, const pa_source_info *i, int is_last, void *userdata ) {

    if ( is_last || device != NULL )
        return;
    assert(i);

	device = pa_xstrdup( i->name );

	if ( ( pa_stream_connect_record( stream, NULL, NULL, flags ) ) < 0 ) {
		fprintf(stderr, "pa_stream_connect_record() failed: %s\n", pa_strerror(pa_context_errno(c)));
		quit(1);
	}
    
}
/*
static void stream_read_callback(pa_stream *s, size_t length, void *userdata) {
	const void *data;

    assert(s);

    assert(length > 0);


    if (pa_stream_peek(s, &data, &length) < 0) {
        fprintf(stderr, "pa_stream_peek() failed: %s\n", pa_strerror(pa_context_errno(context)));
        quit(1);
        return;
    }

    assert(data);

    assert(length > 0);

    int excess = buffer_index * 2 + length - ( BUFSIZE );

    if ( excess < 0 ) excess = 0;

    memcpy( buffer + buffer_index, data, length - excess );
    buffer_index += ( length - excess ) / 2;

    if ( excess ) {
        memcpy( snapshot, buffer, buffer_index * 2 );
        buffer_index = 0;
    }

    pa_stream_drop(s);
}
*/
static void stream_read_callback(pa_stream *s, size_t length, void *userdata) {
	pa_threaded_mainloop_signal(mainloop, 0);
}

static void context_state_callback(pa_context *c, void *userdata) {

    switch (pa_context_get_state(c)) {
        case PA_CONTEXT_CONNECTING:
        case PA_CONTEXT_AUTHORIZING:
        case PA_CONTEXT_SETTING_NAME:
            break;
        case PA_CONTEXT_READY:
            assert(c);
            assert(!stream);

            if (!(stream = pa_stream_new(c, stream_name, &sample_spec, channel_map_set ? &channel_map : NULL))) {
                fprintf(stderr, "pa_stream_new() failed: %s\n", pa_strerror(pa_context_errno(c)));
                quit(1);
            }

            pa_stream_set_read_callback(stream, stream_read_callback, NULL);

            pa_operation_unref( pa_context_get_source_info_list( c, get_source_info_callback, NULL ) );

            break;
        case PA_CONTEXT_TERMINATED:
            quit(0);
            break;

        case PA_CONTEXT_FAILED:
        default:
            fprintf(stderr, "Connection failure: %s\n", pa_strerror(pa_context_errno(c)));
            quit(1);
    }
}

int
initialize()
{
	int r;
    char *server = NULL;

    client_name = pa_xstrdup( "julius" );
    stream_name = pa_xstrdup( "julius" );

    // Set up a new main loop
    if ( ! ( mainloop = pa_threaded_mainloop_new( ) ) ) {
        fprintf( stderr, "pa_mainloop_new() failed.\n" );
        return;
    }

    mainloop_api = pa_threaded_mainloop_get_api( mainloop );

    r = pa_signal_init( mainloop_api );
    assert( r == 0 );

    // create a new connection context
    if ( ! ( context = pa_context_new( mainloop_api, client_name ) ) ) {
        fprintf( stderr, "pa_context_new() failed.\n" );
        return;
    }
    pa_context_set_state_callback( context, context_state_callback, NULL );

    // Connect the context
    pa_context_connect( context, server, 0, NULL );

    // pulseaudio thread
    pa_threaded_mainloop_start( mainloop );
	
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


boolean
adin_standby(int sfreq, void *dummy)
{	
  return TRUE;
}
 
boolean
adin_open(char *pathname)
{
	return(TRUE);
}

const void *mybuffer;
size_t read_index, read_length;
	
int myread(void*data, size_t length) {
	
    pa_threaded_mainloop_lock(mainloop);

    while (length > 0) {
        size_t l;

        while (!mybuffer) {
            int r;

            r = pa_stream_peek(stream, &mybuffer, &read_length);

            if (!mybuffer) {
                pa_threaded_mainloop_wait(mainloop);
            } else
                read_index = 0;
        }

        l = read_length < length ? read_length : length;
        memcpy(data, (const uint8_t*) mybuffer+read_index, l);

        data = (uint8_t*) data + l;
        length -= l;

        read_index += l;
        read_length -= l;

        if (!read_length) {
            int r;

            r = pa_stream_drop(stream);
			mybuffer = NULL;
            read_length = 0;
            read_index = 0;
        }
    }

    pa_threaded_mainloop_unlock(mainloop);
    return 0;
}

int
adin_read(SP16 * buf, int sampnum)
{	
	int cnt, bufsize;
	bufsize = sampnum * sizeof(SP16);
	
	if (bufsize > BUFSIZE) bufsize = BUFSIZE;
	myread(buf, bufsize);
	
	
	/*
	const void *data;
	size_t rb;
	 
    if(pa_stream_peek(stream,&data,&rb)<0){
        printf("Failed to read data from stream\n");
        return;
    }
	
	 * 
	
	memcpy(buf, data, rb);
 
    //pa_stream_drop(stream);
	*/
	
	/*
	if (pa_simple_read(r, buf, bufsize, &errorpa) < 0) {
		printf("Error: adin_pulseaudio: pa_simple_read() failed: %s\n", pa_strerror(errorpa));
		return (-2);
	}
	*/
	cnt = bufsize / sizeof(SP16);
	return(cnt);
	
}

boolean
adin_close()
{
	//pa_threaded_mainloop_signal(mainloop, 0);
	//
	//pa_signal_done();
	//pa_threaded_mainloop_unlock(mainloop);
	assert( mainloop_api );
	mainloop_api->quit(mainloop_api, 0);
	pa_context_unref(context);
	pa_threaded_mainloop_stop(mainloop);
	
	/*
	//ALTERNATIVE 1
	mainloop_api->quit(mainloop_api, 0);
	pa_context_unref(context);

    for (i = 0; i < NSTREAMS; i++)
        if (streams[i])
            pa_stream_unref(streams[i]);

    pa_mainloop_free(m);
	
	// ALTERNATIVE 2
	pa_threaded_mainloop_stop ( mainloop );

	if ( stream )
			pa_stream_unref ( stream );

	if ( context )
			pa_context_unref ( context );


	if ( stdio_event )
	{
			assert ( mainloop_api );
			mainloop_api->io_free ( stdio_event );
	}


	if ( time_event )
	{
			assert ( mainloop_api );
			mainloop_api->time_free ( time_event );
	}

	if ( mainloop_api )
			mainloop_api->quit ( mainloop_api, 0 );

	if ( mainloop )
	{
			pa_signal_done();
			pa_threaded_mainloop_free ( mainloop );
	}

	if ( buffer )
			pa_xfree ( buffer );

	if ( server )
			pa_xfree ( server );

	if ( device )
			pa_xfree ( device );

	if ( client_name )
			pa_xfree ( client_name );

	if ( stream_name )
			pa_xfree ( stream_name );
	*/
	
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
