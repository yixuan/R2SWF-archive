STATICLIB = libz.a

CFLAGS = -std=gnu99 -O3 -Wall
EXTRA_CFLAGS = -DNO_VIZ -DHAVE_UNISTD_H

CC = $(BINPREF)gcc
LD = $(CC)
LDFLAGS =

AR = $(BINPREF)ar
ARFLAGS = rcs

CP = cp -fp
RM = rm -f


OBJS = adler32.o compress.o crc32.o deflate.o gzclose.o gzlib.o gzread.o \
       gzwrite.o infback.o inffast.o inflate.o inftrees.o trees.o uncompr.o zutil.o


all: $(STATICLIB)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c -o $@ $<

$(STATICLIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

.PHONY: install clean

clean:
	-$(RM) $(STATICLIB)
	-$(RM) *.o


adler32.o: zlib.h zconf.h
compress.o: zlib.h zconf.h
crc32.o: crc32.h zlib.h zconf.h
deflate.o: deflate.h zutil.h zlib.h zconf.h
gzclose.o: zlib.h zconf.h gzguts.h
gzlib.o: zlib.h zconf.h gzguts.h
gzread.o: zlib.h zconf.h gzguts.h
gzwrite.o: zlib.h zconf.h gzguts.h
inffast.o: zutil.h zlib.h zconf.h inftrees.h inflate.h inffast.h
inflate.o: zutil.h zlib.h zconf.h inftrees.h inflate.h inffast.h
infback.o: zutil.h zlib.h zconf.h inftrees.h inflate.h inffast.h
inftrees.o: zutil.h zlib.h zconf.h inftrees.h
trees.o: deflate.h zutil.h zlib.h zconf.h trees.h
uncompr.o: zlib.h zconf.h
zutil.o: zutil.h zlib.h zconf.h
