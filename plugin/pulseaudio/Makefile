SHELL=/bin/sh

.SUFFIXES:
.SUFFIXES: .c .jpi
.c.jpi:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

CC=gcc
CFLAGS=-shared `/home/psc/11h11/code/julius/pulseaudio/bin/libsent-config --cflags` `/home/psc/11h11/code/julius/pulseaudio/bin/libjulius-config --cflags`
LDFLAGS=`/home/psc/11h11/code/julius/pulseaudio/bin/libjulius-config --libs` `/home/psc/11h11/code/julius/pulseaudio/bin/libsent-config --libs` -Wl,--export-dynamic -Wl,--whole-archive ../../common/libpd.a -Wl,--no-whole-archive

all: adin_pulseaudiolibpd.jpi

calcmix.jpi: calcmix.c
	$(CC) $(CFLAGS) $(J_CFLAGS) -o calcmix.jpi $(LDFLAGS) $(J_LDFLAGS) calcmix.c

generic_callback.jpi: generic_callback.c
	$(CC) $(CFLAGS) $(J_CFLAGS) -o generic_callback.jpi generic_callback.c $(LDFLAGS) $(J_LDFLAGS)

clean:
	rm *.jpi
