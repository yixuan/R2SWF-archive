STATICLIB = libz.a

CFLAGS = -std=gnu99 -O3 -Wall $(CPICFLAGS)
EXTRA_CFLAGS = -DNO_VIZ -DHAVE_UNISTD_H

LD = $(CC)
LDFLAGS =

ARFLAGS = rcs

CP = cp -fp
RM = rm -f


OBJS = adler32.o compress.o crc32.o deflate.o gzclose.o gzlib.o gzread.o \
       gzwrite.o infback.o inffast.o inflate.o inftrees.o trees.o uncompr.o zutil.o


all: $(STATICLIB)

%.o: %.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c -o $@ $<

$(STATICLIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

.PHONY: install clean

clean:
	-$(RM) $(STATICLIB)
	-$(RM) *.o

