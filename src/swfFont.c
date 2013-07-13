#include "swfFont.h"

SEXP swfLoadFont(SEXP fontPath)
{
    const char* filePath = CHAR(STRING_ELT(fontPath, 0));
    pfontDesc font = (pfontDesc) calloc(1, sizeof(fontDesc));
    SEXP extPtr;
    
    FT_Init_FreeType(&(font->library));
    FT_New_Face(font->library, filePath, 0, &(font->face));
    
    font->font = newSWFFont_fromFile(filePath);
    
    extPtr = R_MakeExternalPtr(font, R_NilValue, R_NilValue);
    return extPtr;
}

SEXP swfCleanFont(SEXP extPtr)
{
    pfontDesc font = (pfontDesc) R_ExternalPtrAddr(extPtr);
    
    if(font->face) FT_Done_Face(font->face);
    if(font->library) FT_Done_FreeType(font->library);
    if(font->font) destroySWFFont(font->font);
    if(font) free(font);
    
    return R_NilValue;
}