ZLIBINC = ../zlib
ZLIBLIB = ../zlib
ZLIB = $(ZLIBLIB)/libz.a

CP = cp -fp
RM = rm -f

LD = $(CC)
AR_RC = $(AR) rcs

CRELEASE = -O3
LDRELEASE = -s
CFLAGS = -std=gnu99 $(CRELEASE) -Wall $(CPICFLAGS)
LDFLAGS = $(LDRELEASE)

O=.o
A=.a

OBJS =  png$(O) pngerror$(O) pngget$(O) pngmem$(O) pngpread$(O) \
	pngread$(O) pngrio$(O) pngrtran$(O) pngrutil$(O) pngset$(O) \
	pngtrans$(O) pngwio$(O) pngwrite$(O) pngwtran$(O) pngwutil$(O)


all: libpng$(A)

%.o: %.c
	$(CC) $(CFLAGS) -I$(ZLIBINC) -c -o $@ $<

libpng$(A): $(OBJS)
	$(AR_RC) $@ $(OBJS)


.PHONY: install clean

clean:
	-$(RM) libpng$(A)
	-$(RM) *$(O) 

