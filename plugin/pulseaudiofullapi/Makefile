SHELL=/bin/sh

.SUFFIXES:
.SUFFIXES: .c .jpi
.c.jpi:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

CC=gcc
CFLAGS=-shared `/home/psc/11h11/code/julius/julius/bin/libsent-config --cflags` `/home/psc/11h11/code/julius/julius/bin/libjulius-config --cflags` `pkg-config --cflags libpulse`
LDFLAGS=`/home/psc/11h11/code/julius/julius/bin/libjulius-config --libs` `/home/psc/11h11/code/julius/julius/bin/libsent-config --libs` `pkg-config --libs libpulse` -Wl,--export-dynamic -Wl,--whole-archive ../../common/libpd.a -Wl,--no-whole-archive

all: adin_pulseaudiolibpdfull.jpi

calcmix.jpi: calcmix.c
	$(CC) $(CFLAGS) $(J_CFLAGS) -o calcmix.jpi $(LDFLAGS) $(J_LDFLAGS) calcmix.c

generic_callback.jpi: generic_callback.c
	$(CC) $(CFLAGS) $(J_CFLAGS) -o generic_callback.jpi generic_callback.c $(LDFLAGS) $(J_LDFLAGS)

clean:
	rm *.jpi
