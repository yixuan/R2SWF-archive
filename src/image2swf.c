#include <libming.h>
#include <stdlib.h>
#include <stdio.h>

#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>


SEXP image2swf(SEXP fileNames, SEXP format, SEXP outName,
		       SEXP bgColor, SEXP interval)
{
    SWFMovie m = newSWFMovieWithVersion(8);
    int nFiles = LENGTH(fileNames);
	int i;
	int dimNotSet = 1;
	int swfHeight, swfWidth;
	SWFBitmap image = NULL;
	const char *filename;
	SWFMovieBlockType ublock;

    SWFMovie_setBackground(m,
			               INTEGER(bgColor)[0],
						   INTEGER(bgColor)[1],
						   INTEGER(bgColor)[2]);
	SWFMovie_setRate(m, (float) 1.0 / REAL(interval)[0]);

    for(i = 0; i < nFiles; i++)
	{
		filename = CHAR(STRING_ELT(fileNames, i));
		/* 1 for png, 2 for jpeg/jpg, 0 for other */
		if(INTEGER(format)[i] == 1)
		{
			image = (SWFBitmap) newSWFDBLBitmapData_fromPngFile(filename);
		} else if(INTEGER(format)[i] == 2) {
			FILE *fp = fopen(filename, "rb");
			if(fp == NULL)
			{
				image = NULL;
			} else {
				image = (SWFBitmap) newSWFJpegBitmap(fp);
			}
		} else {
			image = NULL;
		}
		
		if(image == NULL)
		{
			Rf_warning("Unsupported file \"%s\", ignored.\n", filename);
			continue;
		}
		if(dimNotSet)
		{
			swfHeight = SWFBitmap_getHeight(image);
		    swfWidth = SWFBitmap_getWidth(image);
			SWFMovie_setDimension(m, swfHeight, swfWidth);
			dimNotSet = 0;
		}

		if(INTEGER(format)[i] == 1)
		{
			ublock.dblbmp_data = (SWFDBLBitmapData) image;
			SWFMovie_add_internal(m, ublock);
			SWFMovie_nextFrame(m);
		} else if(INTEGER(format)[i] == 2) {
			ublock.jpegbmp = (SWFJpegBitmap) image;
			SWFMovie_add_internal(m, ublock);
			SWFMovie_nextFrame(m);
		}
	}
    SWFMovie_save(m, CHAR(STRING_ELT(outName, 0)));
	destroySWFMovie(m);

    return R_NilValue;
}

