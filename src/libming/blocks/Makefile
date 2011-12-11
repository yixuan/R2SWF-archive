ZLIBINC = ../../zlib
ZLIBLIB = ../../zlib
ZLIB = $(ZLIBLIB)/libz.a

LIBPNGINC = ../../libpng
LIBPNGLIB = ../../libpng
LIBPNG = $(LIBPNGLIB)/libpng.a

CP = cp -fp
RM = rm -f

OBJS = binary.o bitmap.o block.o \
	browserfont.o character.o cxform.o \
	dbl.o error.o fdbfont.o fileattrs.o \
	fillstyle.o filter.o flv.o \
	font.o fromswf.o \
	gifdbl.o gradient.o imports.o \
	input.o jpeg.o linestyle.o \
	matrix.o metadata.o method.o \
	morph.o mp3.o output.o \
	outputblock.o placeobject.o pngdbl.o \
	protect.o rect.o scalinggrid.o \
	scenedata.o scriptlimits.o shape.o \
	sound.o soundinstance.o soundstream.o \
	sprite.o symbolclass.o tabindex.o \
	text.o textfield.o \
	utf8.o videostream.o

all: $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -I$(ZLIBINC) -I$(LIBPNGINC) $(CPPFLAGS) -I. -I.. -c $< -o $@

