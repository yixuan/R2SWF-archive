ZLIBINC = ../zlib
ZLIBLIB = ../zlib
ZLIB = $(ZLIBLIB)/libz.a

CP = cp -fp
RM = rm -f

LD = $(CC)
AR_RC = $(AR) rcs

LDRELEASE = -s
LDFLAGS = $(LDRELEASE)

O=.o
A=.a

OBJS =  png$(O) pngerror$(O) pngget$(O) pngmem$(O) pngpread$(O) \
	pngread$(O) pngrio$(O) pngrtran$(O) pngrutil$(O) pngset$(O) \
	pngtrans$(O) pngwio$(O) pngwrite$(O) pngwtran$(O) pngwutil$(O)


all: libpng$(A)

.c.o:
	$(CC) $(CFLAGS) -I$(ZLIBINC) $(CPPFLAGS) -c $< -o $@

libpng$(A): $(OBJS)
	@$(RM) $@
	$(AR_RC) $@ $(OBJS)


.PHONY: install clean

clean:
	-$(RM) libpng$(A)
	-$(RM) *$(O) 

