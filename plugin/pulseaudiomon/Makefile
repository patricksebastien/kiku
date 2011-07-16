SHELL=/bin/sh

.SUFFIXES:
.SUFFIXES: .c .jpi
.c.jpi:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

CC=gcc -fPIC
CFLAGS=-shared `/home/psc/src/juliuscvs/bin/libsent-config --cflags` `/home/psc/src/juliuscvs/bin/libjulius-config --cflags` `pkg-config --cflags libpulse-simple`
LDFLAGS=`/home/psc/src/juliuscvs/bin/libjulius-config --libs` `/home/psc/src/juliuscvs/bin/libsent-config --libs` `pkg-config --libs libpulse-simple` -Wl,--export-dynamic -Wl,--whole-archive ../../common/libpd.a -Wl,--no-whole-archive

all: adin_pulseaudiolibpdmon.jpi

calcmix.jpi: calcmix.c
	$(CC) $(CFLAGS) $(J_CFLAGS) -o calcmix.jpi $(LDFLAGS) $(J_LDFLAGS) calcmix.c

generic_callback.jpi: generic_callback.c
	$(CC) $(CFLAGS) $(J_CFLAGS) -o generic_callback.jpi generic_callback.c $(LDFLAGS) $(J_LDFLAGS)

clean:
	rm *.jpi
