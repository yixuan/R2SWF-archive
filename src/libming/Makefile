ZLIBINC = ../zlib
ZLIBLIB = ../zlib
ZLIB = $(ZLIBLIB)/libz.a

LIBPNGINC = ../libpng
LIBPNGLIB = ../libpng
LIBPNG = $(LIBPNGLIB)/libpng.a

CP = cp -fp
RM = rm -f

LD = $(CC)
AR_RC = $(AR) rcs

LDRELEASE = -s
LDFLAGS = $(LDRELEASE)

O=.o
A=.a

OBJS =  blocklist$(O) compat$(O) displaylist$(O) fill$(O) font_util$(O) \
	gc$(O) ming$(O) movie$(O) movieclip$(O) position$(O) \
	shape_cubic$(O) shape_util$(O) text_util$(O) libming$(O) \
	blocks/binary$(O) blocks/bitmap$(O) blocks/block$(O) \
	blocks/browserfont$(O) blocks/character$(O) blocks/cxform$(O) \
	blocks/dbl$(O) blocks/error$(O) blocks/fdbfont$(O) blocks/fileattrs$(O) \
	blocks/fillstyle$(O) blocks/filter$(O) blocks/flv$(O) \
	blocks/font$(O) blocks/fromswf$(O) \
	blocks/gifdbl$(O) blocks/gradient$(O) blocks/imports$(O) \
	blocks/input$(O) blocks/jpeg$(O) blocks/linestyle$(O) \
	blocks/matrix$(O) blocks/metadata$(O) blocks/method$(O) \
	blocks/morph$(O) blocks/mp3$(O) blocks/output$(O) \
	blocks/outputblock$(O) blocks/placeobject$(O) blocks/pngdbl$(O) \
	blocks/protect$(O) blocks/rect$(O) blocks/scalinggrid$(O) \
	blocks/scenedata$(O) blocks/scriptlimits$(O) blocks/shape$(O) \
	blocks/sound$(O) blocks/soundinstance$(O) blocks/soundstream$(O) \
	blocks/sprite$(O) blocks/symbolclass$(O) blocks/tabindex$(O) \
	blocks/text$(O) blocks/textfield$(O) \
	blocks/utf8$(O) blocks/videostream$(O)


.PHONY: all blocks clean

all: libming$(A)

.c.o:
	$(CC) $(CFLAGS) -I$(ZLIBINC) -I$(LIBPNGINC) $(CPPFLAGS) -I. -c $< -o $@


libming$(A): blocks $(OBJS)
	@$(RM) $@
	$(AR_RC) $@ $(OBJS)

blocks:
	cd blocks && $(MAKE) all CC="$(CC)" CFLAGS="$(CFLAGS)"


clean:
	-$(RM) libming$(A)
	-$(RM) *$(O)
	-$(RM) blocks/*$(O)

