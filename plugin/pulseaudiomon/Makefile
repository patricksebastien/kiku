PROGRAM = adin_pulseaudiolibpdmon.jpi
PROGRAM_FILES = adin_pulseaudiolibpdmon.c

CC		= gcc
CFLAGS	+= -fPIC -g $(shell /home/psc/src/juliuscvs/bin/libjulius-config --cflags) $(shell /home/psc/src/juliuscvs/bin/libsent-config --cflags) $(shell pkg-config libpulse-simple --cflags)
LDFLAGS	+= -shared -g
LIBS 	+= $(shell /home/psc/src/juliuscvs/bin/libjulius-config --libs) $(shell /home/psc/src/juliuscvs/bin/libsent-config --libs) $(shell pkg-config --libs libpulse-simple) -Wl,--export-dynamic -Wl,--whole-archive ../../common/libpd.a -Wl,--no-whole-archive

all: $(PROGRAM)

%.jpi: %.c
	$(CC) $(PROGRAM_FILES) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(LIBS)

clean:
	@rm -rf $(PROGRAM)

