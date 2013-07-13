#include <ming.h>

#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct fontDesc {
    FT_Library library;
    FT_Face face;
    SWFFont font;
} fontDesc;

typedef fontDesc* pfontDesc;

SEXP swfLoadFont(SEXP fontPath);