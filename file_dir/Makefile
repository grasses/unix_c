ROOT=..
PLATFORM="maxos"
include $(ROOT)/Makefile.mac
PROGS = access stat
#PROGS =	access cdpwd changemod devrdev filetype mycd umask unlink $(ZAP)

all:	$(PROGS) $(MOREPROGS)

%:	%.c $(LIBAPUE)
		$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
		rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o $(ZAP)
