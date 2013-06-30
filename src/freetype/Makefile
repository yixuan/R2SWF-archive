STATICLIB = libfreetype.a

EXTRA_CFLAGS = -DHAVE_FSSPEC=0 -DHAVE_ATS=0 \
	-DFT_CONFIG_OPTION_SYSTEM_ZLIB \
	"-DFT_CONFIG_CONFIG_H=<ftconfig.h>" \
	-DFT2_BUILD_LIBRARY \
	"-DFT_CONFIG_MODULES_H=<ftmodule.h>"


CP = cp -fp
RM = rm -f

LD = $(CC)
AR_RC = $(AR) rcs

LDRELEASE = -s
LDFLAGS = $(LDRELEASE)

OBJS = base/ftsystem.o base/ftdebug.o base/ftinit.o base/ftbase.o \
	base/ftbitmap.o base/ftglyph.o \
	truetype/truetype.o sfnt/sfnt.o autofit/autofit.o smooth/smooth.o \
	psnames/psmodule.o

.PHONY: all clean

all: $(STATICLIB)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(CPPFLAGS) -I./config -I./include -c $< -o $@

$(STATICLIB): $(OBJS)
	@$(RM) $@
	$(AR_RC) $@ $(OBJS)

clean:
	$(RM) $(STATICLIB)
	$(RM) $(OBJS)
	$(RM) *.o

