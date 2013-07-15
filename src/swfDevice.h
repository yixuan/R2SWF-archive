#ifndef SWFDEVICE_H_INCLUDED
#define SWFDEVICE_H_INCLUDED

#include <ming.h>
#include "swfArray.h"
#include "swfFont.h"
#include "swfText.h"

#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>

#define R_USE_PROTOTYPES 1
#include <R_ext/GraphicsEngine.h>
#include <R_ext/GraphicsDevice.h>

/* SWF device specific data */
typedef struct swfDesc {
    char filename[1024]; /* swf filename */
    SWFMovie m;          /* movie object */
    SWFMovieClip currentFrame;
                         /* current frame */
    SWFDisplayItem currentClip;
                         /* current mask/clip layer */
    SWFArray array;      /* store temporary objects */
    SEXP pkgEnv;         /* environment storing objects in R,
                            used to retrieve font objects,
                            defined in font.R */
    FT_Outline_Funcs outlnFuns;
                         /* functions to draw font outline,
                            defined in swfText.h */
} swfDesc;

typedef swfDesc* pswfDesc;

/************************************************************* 
 
 The followings are utility functions used by plotting handlers
 
*************************************************************/
/* Setup the device descriptions data */
Rboolean swfSetup(pDevDesc dev, const char *filename,
    double width, double height,
    const int *bg, float frameRate, SEXP env);

/* Initialize SWF device specific data */
Rboolean swfSetupSWFInfo(pswfDesc swfInfo, const char *filename,
    double width, double height,
    const int *bg, float frameRate, SEXP env);

/* Function to set line style */
void swfSetLineStyle(SWFShape shape, const pGEcontext gc, pswfDesc swfInfo);
/* Function to set fill style */
void swfSetFillStyle(SWFShape shape, const pGEcontext gc, pswfDesc swfInfo);
/* Function to set text color */
void swfSetTextColor(SWFShape shape, const pGEcontext gc, pswfDesc swfInfo);
/* Draw line respecting lty parameter */
void swfDrawStyledLineTo(SWFShape shape, double x, double y, const pGEcontext gc);
/* Get font FT_Face object according to gc parameter */
FT_Face swfGetFTFace(const pGEcontext gc, pswfDesc swfInfo);



/************************************************************* 
 
 Device plotting function hooks. Defined in R_ext/GraphicsDevice.h
 
*************************************************************/
void swfActivate(pDevDesc dd);

void swfCircle(double x, double y, double r, const pGEcontext gc, pDevDesc dd);

void swfClip(double x0, double x1, double y0, double y1, pDevDesc dd);

void swfClose(pDevDesc dd);

void swfDeactivate(pDevDesc dd);

/* static Rboolean swfLocator(double *x, double *y, pDevDesc dd); */

void swfLine(double x1, double y1, double x2, double y2, const pGEcontext gc, pDevDesc dd);

void swfMetricInfo(int c, const pGEcontext gc, double* ascent, double* descent, double* width, pDevDesc dd);

void swfMode(int mode, pDevDesc dd);

void swfNewPage(const pGEcontext gc, pDevDesc dd);

void swfPolygon(int n, double *x, double *y, const pGEcontext gc, pDevDesc dd);

void swfPolyline(int n, double *x, double *y, const pGEcontext gc, pDevDesc dd);

void swfRect(double x0, double y0, double x1, double y1, const pGEcontext gc, pDevDesc dd);

void swfPath(double *x, double *y, int npoly, int *nper, Rboolean winding, const pGEcontext gc, pDevDesc dd);

/*
static void swfRaster(unsigned int *raster, int w, int h,
                      double x, double y, 
                      double width, double height,
                      double rot, 
                      Rboolean interpolate,
                      const pGEcontext gc, pDevDesc dd);
*/

/* static SEXP swfCap(pDevDesc dd); */

void swfSize(double *left, double *right, double *bottom, double *top, pDevDesc dd);

double swfStrWidth(const char *str, const pGEcontext gc, pDevDesc dd);

void swfText(double x, double y, const char *str, double rot, double hadj, const pGEcontext gc, pDevDesc dd);

void swfTextUTF8(double x, double y, const char *str, double rot, double hadj, const pGEcontext gc, pDevDesc dd);

double swfStrWidthUTF8(const char *str, const pGEcontext gc, pDevDesc dd);



#endif /* SWFDEVICE_H_INCLUDED */

