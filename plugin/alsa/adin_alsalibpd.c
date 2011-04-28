/*********************************************************************
 * Author: Patrick Sébastien
 * http://www.workinprogress.ca
 *********************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include <sent/stddefs.h>
#include <sent/adin.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// alsa
#include <alsa/asoundlib.h>

// libpd
#include "../../common/z_libpd.h"

#define MAXPATHLEN 2048

#define PLUGIN_TITLE "Alsa A/D-in plugin for Julius"
#define INPUT_OPT "alsa-libpd"

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

static int srate;		///< Required sampling rate
static snd_pcm_t *handle;	///< Audio handler
static char pcm_name[MAXPATHLEN]; ///< Name of the PCM device
static int latency = 32;	///< Lantency time in msec.  You can override this value by specifying environment valuable "LATENCY_MSEC".
static boolean need_swap;	///< Whether samples need byte swap

#define MAXPOLLINTERVAL 300

#if (SND_LIB_MAJOR == 0)
static struct pollfd *ufds;	///< Poll descriptor
static int count;		///< Poll descriptor count
#endif

static void
output_card_info(char *pcm_name, snd_pcm_t *handle)
{
  int err;
  snd_ctl_t *ctl;
  snd_ctl_card_info_t *info;
  snd_pcm_info_t *pcminfo;
  snd_ctl_card_info_alloca(&info);
  snd_pcm_info_alloca(&pcminfo);
  char ctlname[30];
  int card;
  
  /* get PCM information to set current device and subdevice name */
  if ((err = snd_pcm_info(handle, pcminfo)) < 0) {
    printf("Warning: adin_alsa: failed to obtain pcm info\n");
    printf("Warning: adin_alsa: skip output of detailed audio device info\n");
    return;
  }
  /* open control associated with the pcm device name */
  card = snd_pcm_info_get_card(pcminfo);
  if (card < 0) {
    strcpy(ctlname, "default");
  } else {
    snprintf(ctlname, 30, "hw:%d", card);
  }
  if ((err = snd_ctl_open(&ctl, ctlname, 0)) < 0) {
    printf("Warning: adin_alsa: failed to open control device \"%s\", \n", ctlname);
    printf("Warning: adin_alsa: skip output of detailed audio device info\n");
    return;
  }
  /* get its card info */
  if ((err = snd_ctl_card_info(ctl, info)) < 0) {
    printf("Warning: adin_alsa: unable to get card info for %s\n", ctlname);
    printf("Warning: adin_alsa: skip output of detailed audio device info\n");
    snd_ctl_close(ctl);
    return;
  }

  /* get detailed PCM information of current device from control */
  if ((err = snd_ctl_pcm_info(ctl, pcminfo)) < 0) {
    printf("Error: adin_alsa: unable to get pcm info from card control\n");
    printf("Warning: adin_alsa: skip output of detailed audio device info\n");
    snd_ctl_close(ctl);
    return;
  }
  /* output */
  printf("Stat: \"%s\": %s [%s] device %s [%s] %s\n",
       pcm_name,
       snd_ctl_card_info_get_id(info),
       snd_ctl_card_info_get_name(info),
       snd_pcm_info_get_id(pcminfo),
       snd_pcm_info_get_name(pcminfo),
       snd_pcm_info_get_subdevice_name(pcminfo));

  /* close controller */
  snd_ctl_close(ctl);

}

void
swap_sample_bytes(SP16 *buf, int len)
{
  char *p;
  char t;
  int i;
  
  p = (char *)buf;

  for (i=0;i<len;i++) {
    t = *p;
    *p = *(p + 1);
    *(p + 1) = t;
    p += 2;
  }
}

static int
xrun_recovery(snd_pcm_t *handle, int err)
{
  if (err == -EPIPE) {    /* under-run */
    err = snd_pcm_prepare(handle);
    if (err < 0)
      printf("Error: adin_alsa: can't recovery from PCM buffer underrun, prepare failed: %s\n", snd_strerror(err));
    return 0;
  } else if (err == -ESTRPIPE) {
    while ((err = snd_pcm_resume(handle)) == -EAGAIN)
      sleep(1);       /* wait until the suspend flag is released */
    if (err < 0) {
      err = snd_pcm_prepare(handle);
      if (err < 0)
	printf("Error: adin_alsa: can't recovery from PCM buffer suspend, prepare failed: %s\n", snd_strerror(err));
    }
    return 0;
  }
  return err;
}

boolean
adin_standby(int sfreq, void *dummy)
{	
  srate = sfreq;
  
  return TRUE;
}
 
boolean
adin_open(char *devstr)
{
	
	strcpy(pcm_name, "default");
	devstr = pcm_name;
	int err;
 
  snd_pcm_hw_params_t *hwparams; ///< Pointer to device hardware parameters
#if (SND_LIB_MAJOR == 0)
  int actual_rate;		/* sample rate returned by hardware */
#else
  unsigned int actual_rate;		/* sample rate returned by hardware */
#endif
  int dir = 0;			/* comparison result of exact rate and given rate */

  /* open the device in non-block mode) */
  if ((err = snd_pcm_open(&handle, devstr, SND_PCM_STREAM_CAPTURE, SND_PCM_NONBLOCK)) < 0) {
    printf("Error: adin_alsa: cannot open PCM device \"%s\" (%s)\n", devstr, snd_strerror(err));
    return(FALSE);
  }
  /* set device to non-block mode */
  if ((err = snd_pcm_nonblock(handle, 1)) < 0) {
    printf("Error: adin_alsa: cannot set PCM device to non-blocking mode\n");
    return(FALSE);
  }

  /* allocate hwparam structure */
  snd_pcm_hw_params_alloca(&hwparams);

  /* initialize hwparam structure */
  if ((err = snd_pcm_hw_params_any(handle, hwparams)) < 0) {
    printf("Error: adin_alsa: cannot initialize PCM device parameter structure (%s)\n", snd_strerror(err));
    return(FALSE);
  }

  /* set interleaved read/write format */
  if ((err = snd_pcm_hw_params_set_access(handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
    printf("Error: adin_alsa: cannot set PCM device access mode (%s)\n", snd_strerror(err));
    return(FALSE);
  }

  /* set sample format */
#ifdef WORDS_BIGENDIAN

  /* try big endian, then little endian with byte swap */
  if ((err = snd_pcm_hw_params_set_format(handle, hwparams, SND_PCM_FORMAT_S16_BE)) >= 0) {
    need_swap = FALSE;
  } else if ((err = snd_pcm_hw_params_set_format(handle, hwparams, SND_PCM_FORMAT_S16_LE)) >= 0) {
    need_swap = TRUE;
  } else {
    printf("Error: adin_alsa: cannot set PCM device format to signed 16bit (%s)\n", snd_strerror(err));
    return(FALSE);
  }
#else  /* LITTLE ENDIAN */

  /* try little endian, then big endian with byte swap */
  if ((err = snd_pcm_hw_params_set_format(handle, hwparams, SND_PCM_FORMAT_S16_LE)) >= 0) {
    need_swap = FALSE;
  } else if ((err = snd_pcm_hw_params_set_format(handle, hwparams, SND_PCM_FORMAT_S16_BE)) >= 0) {
    need_swap = TRUE;
  } else {
    printf("Error: adin_alsa: cannot set PCM device format to signed 16bit (%s)\n", snd_strerror(err));
    return(FALSE);
  }
#endif
  /* set number of channels */
  if ((err = snd_pcm_hw_params_set_channels(handle, hwparams, 1)) < 0) {
    printf("Error: adin_alsa: cannot set PCM channel to %d (%s)\n", 1, snd_strerror(err));
    return(FALSE);
  }
  
  /* set sample rate (if the exact rate is not supported by the hardware, use nearest possible rate */
#if (SND_LIB_MAJOR == 0)
  actual_rate = snd_pcm_hw_params_set_rate_near(handle, hwparams, srate, &dir);
  if (actual_rate < 0) {
    printf("Error: adin_alsa: cannot set PCM device sample rate to %d (%s)\n", srate, snd_strerror(actual_rate));
    return(FALSE);
  }
#else
  actual_rate = srate;
  err = snd_pcm_hw_params_set_rate_near(handle, hwparams, &actual_rate, &dir);
  if (err < 0) {
    printf("Error: adin_alsa: cannot set PCM device sample rate to %d (%s)\n", srate, snd_strerror(err));
    return(FALSE);
  }
#endif
  if (actual_rate != srate) {
    printf("Warning: adin_alsa: the exact rate %d Hz is not available by your PCM hardware.\n", srate);
    printf("Warning: adin_alsa: using %d Hz instead.\n", actual_rate);
  }
  printf("Stat: capture audio at %dHz\n", actual_rate);

  /* set period size */
  {
#if (SND_LIB_MAJOR == 0)
    int periodsize;		/* period size (bytes) */
    int actual_size;
    int maxsize, minsize;
#else
    unsigned int period_time, period_time_current;
    snd_pcm_uframes_t chunk_size;
    boolean has_current_period;
#endif
    boolean force = FALSE;
    char *p;
    
    /* set apropriate period size */
    if ((p = getenv("LATENCY_MSEC")) != NULL) {
      latency = atoi(p);
      printf("Stat: adin_alsa: trying to set latency to %d msec from LATENCY_MSEC)\n", latency);
      force = TRUE;
    }

    /* get hardware max/min size */
#if (SND_LIB_MAJOR == 0)
    if ((maxsize = snd_pcm_hw_params_get_period_size_max(hwparams, &dir)) < 0) {
      printf("Error: adin_alsa: cannot get maximum period size\n");
      return(FALSE);
    }
    if ((minsize = snd_pcm_hw_params_get_period_size_min(hwparams, &dir)) < 0) {
      printf("Error: adin_alsa: cannot get minimum period size\n");
      return(FALSE);
    }
#else    
    has_current_period = TRUE;
    if ((err = snd_pcm_hw_params_get_period_time(hwparams, &period_time_current, &dir)) < 0) {
      has_current_period = FALSE;
    }
    if (has_current_period) {
      printf("Stat: adin_alsa: current latency time: %d msec\n", period_time_current / 1000);
    }
#endif

    /* set period time (near value will be used) */
#if (SND_LIB_MAJOR == 0)
    periodsize = actual_rate * latency / 1000 * sizeof(SP16);
    if (periodsize < minsize) {
      printf("Stat: adin_alsa: PCM latency of %d ms (%d bytes) too small, use device minimum %d bytes\n", latency, periodsize, minsize);
      periodsize = minsize;
    } else if (periodsize > maxsize) {
      printf("Stat: adin_alsa: PCM latency of %d ms (%d bytes) too large, use device maximum %d bytes\n", latency, periodsize, maxsize);
      periodsize = maxsize;
    }
    actual_size = snd_pcm_hw_params_set_period_size_near(handle, hwparams, periodsize, &dir);
    if (actual_size < 0) {
      printf("Error: adin_alsa: cannot set PCM record period size to %d (%s)\n", periodsize, snd_strerror(actual_size));
      return(FALSE);
    }
    if (actual_size != periodsize) {
      printf("Stat: adin_alsa: PCM period size: %d bytes (%dms) -> %d bytes\n", periodsize, latency, actual_size);
    }
    printf("Stat: Audio I/O Latency = %d msec (data fragment = %d frames)\n", actual_size * 1000 / (actual_rate * sizeof(SP16)), actual_size / sizeof(SP16));
#else
    period_time = latency * 1000;
    if (!force && has_current_period && period_time > period_time_current) {
	printf("Stat: adin_alsa: current latency (%dms) is shorter than %dms, leave it\n", period_time_current / 1000, latency);
	period_time = period_time_current;
    } else {
      if ((err = snd_pcm_hw_params_set_period_time_near(handle, hwparams, &period_time, 0)) < 0) {
	printf("Error: adin_alsa: cannot set PCM record period time to %d msec (%s)\n", period_time / 1000, snd_strerror(err));
	return(FALSE);
      }
      snd_pcm_hw_params_get_period_size(hwparams, &chunk_size, 0);
      //printf("Stat: adin_alsa: latency set to %d msec (chunk = %d bytes)\n", period_time / 1000, chunk_size);
    }
#endif

#if (SND_LIB_MAJOR == 0)
    /* set number of periods ( = 2) */
    if ((err = snd_pcm_hw_params_set_periods(handle, hwparams, sizeof(SP16), 0)) < 0) {
      printf("Error: adin_alsa: cannot set PCM number of periods to %d (%s)\n", sizeof(SP16), snd_strerror(err));
      return(FALSE);
    }
#endif
  }

  /* apply the configuration to the PCM device */
  if ((err = snd_pcm_hw_params(handle, hwparams)) < 0) {
    printf("Error: adin_alsa: cannot set PCM hardware parameters (%s)\n", snd_strerror(err));
    return(FALSE);
  }

  /* prepare for recording */
  if ((err = snd_pcm_prepare(handle)) < 0) {
    printf("Error: adin_alsa: failed to prepare audio interface (%s)\n", snd_strerror(err));
  }

#if (SND_LIB_MAJOR == 0)
  /* prepare for polling */
  count = snd_pcm_poll_descriptors_count(handle);
  if (count <= 0) {
    printf("Error: adin_alsa: invalid PCM poll descriptors count\n");
    return(FALSE);
  }
  ufds = mymalloc(sizeof(struct pollfd) * count);
  if ((err = snd_pcm_poll_descriptors(handle, ufds, count)) < 0) {
    printf("Error: adin_alsa: unable to obtain poll descriptors for PCM recording (%s)\n", snd_strerror(err));
    return(FALSE);
  }
#endif

  /* output status */
  output_card_info(devstr, handle);

	return(TRUE);
}

int
adin_read(SP16 * buf, int sampnum)
{	
	int cnt, bufsize;

	// libpd
	
	
#if (SND_LIB_MAJOR == 0)

  snd_pcm_sframes_t avail;

  while ((avail = snd_pcm_avail_update(handle)) <= 0) {
    usleep(latency * 1000);
  }
  if (avail < sampnum) {
	bufsize = avail;
	SP16 inbuf[bufsize];
    cnt = snd_pcm_readi(handle, inbuf, avail);
  } else {
	  bufsize = sampnum;
	SP16 inbuf[bufsize];
    cnt = snd_pcm_readi(handle, inbuf, sampnum);
  }

#else

  int ret;
  snd_pcm_status_t *status;
  int res;
  struct timeval now, diff, tstamp;

  SP16 inbuf[sampnum * sizeof(SP16)];

  ret = snd_pcm_wait(handle, MAXPOLLINTERVAL);
  switch (ret) {
  case 0:			/* timeout */
    printf("Warning: adin_alsa: no data fragment after %d msec?\n", MAXPOLLINTERVAL);
    cnt = 0;
    break;
  case 1:			/* has data */
    cnt = snd_pcm_readi(handle, inbuf, sampnum); /* read available (non-block) */
	// libpd
	libpd_process_short(inbuf, buf);
    break;
  case -EPIPE:			/* pipe error */
    /* try to recover the broken pipe */
    snd_pcm_status_alloca(&status);
    if ((res = snd_pcm_status(handle, status))<0) {
      printf("Error: adin_alsa: broken pipe: status error (%s)\n", snd_strerror(res));
      return -2;
    }
    if (snd_pcm_status_get_state(status) == SND_PCM_STATE_XRUN) {
      gettimeofday(&now, 0);
      snd_pcm_status_get_trigger_tstamp(status, &tstamp);
      timersub(&now, &tstamp, &diff);
      printf("Warning: adin_alsa: overrun!!! (at least %.3f ms long)\n",
	   diff.tv_sec * 1000 + diff.tv_usec / 1000.0);
      if ((res = snd_pcm_prepare(handle))<0) {
	printf("Error: adin_alsa: overrun: prepare error (%s)", snd_strerror(res));
	return -2;
      }
      break;         /* ok, data should be accepted again */
    } else if (snd_pcm_status_get_state(status) == SND_PCM_STATE_DRAINING) {
      printf("Warning: adin_alsa: draining: capture stream format change? attempting recover...\n");
      if ((res = snd_pcm_prepare(handle))<0) {
	printf("Error: adin_alsa: draining: prepare error (%s)", snd_strerror(res));
	return -2;
      }
      break;
    }
    printf("Error: adin_alsa: error in snd_pcm_wait() (%s)\n", snd_pcm_state_name(snd_pcm_status_get_state(status)));
    return -2;

  default:			/* other poll error */
    printf("Error: adin_alsa: error in snd_pcm_wait() (%s)\n", snd_strerror(ret));
    return(-2);			/* error */
  }
#endif


  if (cnt < 0) {
    printf("Error: adin_alsa: failed to read PCM (%s)\n", snd_strerror(cnt));
    return(-2);
  }
	if (need_swap) {
    swap_sample_bytes(inbuf, cnt);
  }
  
  
  
 

  return(cnt);
}

boolean
adin_close()
{
	int err;

  if ((err = snd_pcm_close(handle)) < 0) {
    printf("Error: adin_alsa: cannot close PCM device (%s)\n", snd_strerror(err));
    return(FALSE);
  }
  return(TRUE);
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
