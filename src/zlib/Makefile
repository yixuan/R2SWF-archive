STATICLIB = libz.a

EXTRA_CFLAGS = -DNO_VIZ -DHAVE_UNISTD_H

LD = $(CC)
LDFLAGS =

ARFLAGS = rcs

CP = cp -fp
RM = rm -f


OBJS = adler32.o compress.o crc32.o deflate.o gzclose.o gzlib.o gzread.o \
  gzwrite.o infback.o inffast.o inflate.o inftrees.o trees.o uncompr.o zutil.o


all: $(STATICLIB)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(CPPFLAGS) -c $< -o $@

$(STATICLIB): $(OBJS)
	@$(RM) $@
	$(AR) $(ARFLAGS) $@ $(OBJS)

.PHONY: install clean

clean:
	-$(RM) $(STATICLIB)
	-$(RM) *.o

