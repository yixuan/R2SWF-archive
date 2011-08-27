ZLIBINC = ../zlib
ZLIBLIB = ../zlib
ZLIB = $(ZLIBLIB)/libz.a

CP = cp -fp
RM = rm -f

CC = $(BINPREF)gcc
LD = $(CC)
AR_RC = $(BINPREF)ar rcs

CRELEASE = -O2
LDRELEASE = -s
CFLAGS = -Wall $(CRELEASE)
LDFLAGS = $(LDRELEASE)

O=.o
A=.a

OBJS =  png$(O) pngerror$(O) pngget$(O) pngmem$(O) pngpread$(O) \
	pngread$(O) pngrio$(O) pngrtran$(O) pngrutil$(O) pngset$(O) \
	pngtrans$(O) pngwio$(O) pngwrite$(O) pngwtran$(O) pngwutil$(O)


all: libpng$(A)

.c$(O):
	$(CC) -c $(CFLAGS) -I$(ZLIBINC) $<

libpng$(A): $(OBJS)
	$(AR_RC) $@ $(OBJS)


.PHONY: install clean

clean:
	-$(RM) libpng$(A)
	-$(RM) *$(O) 


png$(O):      png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngerror$(O): png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngget$(O):   png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngmem$(O):   png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngpread$(O): png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngread$(O):  png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngrio$(O):   png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngrtran$(O): png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngrutil$(O): png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngset$(O):   png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngtrans$(O): png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngwio$(O):   png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngwrite$(O): png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngwtran$(O): png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngwutil$(O): png.h pngconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
