/* src/ming_config.h.  Generated from ming_config.h.in by configure.  */
/* src/ming_config.h.in.  Generated from configure.in by autoheader.  */

#ifndef __MING_CONFIG_H
#define __MING_CONFIG_H


/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Define to 1 if you have the `getopt' function. */
/* #undef HAVE_GETOPT */

/* Define to 1 if you have the <getopt.h> header file. */
/* #undef HAVE_GETOPT_H */

/* Define to 1 if you have the `getopt_long' function. */
/* #undef HAVE_GETOPT_LONG */

/* Define to 1 if you have the <gif_lib.h> header file. */
/* #undef HAVE_GIF_LIB_H */

/* Define to 1 if you have the <inttypes.h> header file. */
/* #undef HAVE_INTTYPES_H */

/* Define to 1 if you have the <memory.h> header file. */
/* #undef HAVE_MEMORY_H */

/* Define to 1 if you have the `mkstemp' function. */
/* #undef HAVE_MKSTEMP */

/* Define to 1 if you have the <stdint.h> header file. */
/* #undef HAVE_STDINT_H */

/* Define to 1 if you have the <stdlib.h> header file. */
/* #undef HAVE_STDLIB_H */

/* Define to 1 if you have the <strings.h> header file. */
/* #undef HAVE_STRINGS_H */

/* Define to 1 if you have the <string.h> header file. */
/* #undef HAVE_STRING_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
/* #undef HAVE_SYS_STAT_H */

/* Define to 1 if you have the <sys/types.h> header file. */
/* #undef HAVE_SYS_TYPES_H */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `vasprintf' function. */
/* #undef HAVE_VASPRINTF */

/* Define to 1 if you have the <zlib.h> header file. */
/* #undef HAVE_ZLIB_H */

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Name of package */
#define PACKAGE "ming"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "ming"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "ming 0.4.3"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "ming"

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.4.3"

/* Define to 1 if you have the ANSI C header files. */
/* #undef STDC_HEADERS */

/* Define this if you want Ming to track all objects allocations. Ming will
   mantain a doubly linked list of allocated objects, call
   Ming_collectGarbage() to get rid of them all */
#define TRACK_ALLOCS 1

/* Use c++ */
/* #undef USE_CXX */

/* Use freetype library */
/* #undef USE_FREETYPE */

/* Use gif library */
/* #undef USE_GIF */

/* Use png library */
#define USE_PNG 1

/* Use zlib */
#define USE_ZLIB 1

/* Version number of package */
#define VERSION "0.4.3"

#endif

