#include "libming.h"
#include <R.h>
#include <stdlib.h>

void png2swf(char** inputPics, int* nPics, double* interval, char** outputFileName)
{
    SWFMovie m = newSWFMovie();
    SWFMovie_setRate(m, 1/interval[0]);
    SWFMovie_setNumberOfFrames(m, nPics[0]);

    int swfHeight = 672, swfWidth = 672;
    int i, dimensionSet=0;
    SWFDBLBitmapData image = NULL ;

    for(i = 0; i < nPics[0]; i++)
    {
        image = newSWFDBLBitmapData_fromPngFile(inputPics[i]);
        if(image == NULL)
        {
            Rprintf("File \"%s\" cannot be opened. Skipped.\n", inputPics[i]);
            continue;
        }
        if(dimensionSet)
        {
            SWFMovie_add(m, (SWFBlock) image);
            if(i < nPics[0]-1) SWFMovie_nextFrame(m);
        }
        else
        {
            swfHeight = SWFBitmap_getHeight((SWFBitmap) image);
            swfWidth = SWFBitmap_getWidth((SWFBitmap) image);
            SWFMovie_setDimension(m, swfHeight, swfWidth);
            dimensionSet = 1;

            SWFMovie_add(m, (SWFBlock) image);
            if(i < nPics[0]-1) SWFMovie_nextFrame(m);
        }
    }

    SWFMovie_save(m, outputFileName[0]);

    destroySWFBitmap((SWFBitmap) image);
    destroySWFMovie(m);
}
