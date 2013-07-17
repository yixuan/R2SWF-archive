#ifndef SWFFONT_H_INCLUDED
#define SWFFONT_H_INCLUDED

#include <ming.h>

#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct fontDesc {
    FT_Library library;
    FT_Face face;
} fontDesc;

typedef fontDesc* pfontDesc;

SEXP swfLoadFont(SEXP fontPath);
SEXP swfCleanFont(SEXP extPtr);

#endif /* SWFFONT_H_INCLUDED */

