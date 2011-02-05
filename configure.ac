AC_PREREQ(2.50)
AC_INIT([R2SWF], [0.1], [yixuan.qiu@cos.name])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX

# Checks for libraries.
## zlib ##
AC_CHECK_LIB([z], [deflate], [ZLIB_LIBS=-lz], [ZLIB_LIBS=])
if test "${ZLIB_LIBS}" = ""; then
  echo ""
  echo "**************************************************"
  echo "Error: zlib not found."
  echo "If you have not installed zlib, you can download"
  echo "the source code from http://www.zlib.net/"
  echo "**************************************************"
  echo ""
  exit 1
fi

## libpng ##
AC_CHECK_LIB([png], [png_init_io], [PNG_LIBS=-lpng], [PNG_LIBS=])
if test "${PNG_LIBS}" = ""; then
  echo ""
  echo "**************************************************"
  echo "Error: libpng not found."
  echo "If you have not installed libpng, you can download"
  echo "the source code from http://www.libpng.org/"
  echo "**************************************************"
  echo ""
  exit 1
fi

## libfreetype ##
AC_CHECK_PROG([HAVE_FREETYPE_CONFIG], [freetype-config], [yes], [no])
if test "x$HAVE_FREETYPE_CONFIG" = "xyes"; then
  FT_CPPFLAGS="`freetype-config --cflags`"
  FT_LIBS="`freetype-config --libs`"
else
  echo ""
  echo "**************************************************"
  echo "Error: freetype-config not found."
  echo "Please install libfreetype with freetype-config"
  echo "script. If you have not installed libfreetype, you"
  echo "can download the source code from"
  echo "http://www.freetype.org/"
  echo "**************************************************"
  echo ""
  exit 1
fi

## libxml2 ##
AC_CHECK_PROG([HAVE_XML2_CONFIG], [xml2-config], [yes], [no])
if test "x$HAVE_XML2_CONFIG" = "xyes"; then
  XML2_CPPFLAGS="`xml2-config --cflags`"
  XML2_LIBS="`xml2-config --libs`"
else
  echo ""
  echo "**************************************************"
  echo "Error: xml2-config not found."
  echo "Please install libxml2 with xml2-config script. If"
  echo "you have not installed libxml2, you can download"
  echo "the source code from http://xmlsoft.org/"
  echo "**************************************************"
  echo ""
  exit 1
fi

## libxslt ##
AC_CHECK_PROG([HAVE_XSLT_CONFIG], [xslt-config], [yes], [no])
if test "x$HAVE_XSLT_CONFIG" = "xyes"; then
  XSLT_CPPFLAGS="`xslt-config --cflags`"
  XSLT_LIBS="`xslt-config --libs` -lexslt"
else
  echo ""
  echo "**************************************************"
  echo "Error: xslt-config not found."
  echo "Please install libxslt with xslt-config script. If"
  echo "you have not installed libxslt, you can download"
  echo "the source code from http://xmlsoft.org/"
  echo "**************************************************"
  echo ""
  exit 1
fi

PKG_CPPFLAGS="-I. ${FT_CPPFLAGS} ${XML2_CPPFLAGS} ${XSLT_CPPFLAGS}"
PKG_LIBS="${XSLT_LIBS} ${XML2_LIBS} ${FT_LIBS} ${PNG_LIBS} ${ZLIB_LIBS} -lm"

AC_SUBST(PKG_CPPFLAGS)
AC_SUBST(PKG_LIBS)
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT
 
