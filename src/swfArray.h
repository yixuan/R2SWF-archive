/*
  Resizeable arrays. Mainly used to store SWF objects and destroy
  them after writing movie to file.
*/

#ifndef MING_ARRAY_H
#define MING_ARRAY_H

#include <ming.h>
#include <blocks/error.h>
#include <stdlib.h>


typedef void* SWFObject;

struct SWFArray_s {
    SWFObject *data;
    int len;
    int alloc_len;
};

typedef struct SWFArray_s* SWFArray;

SWFArray newSWFArray(int initialSize);
void SWFArray_append(SWFArray array, SWFObject obj);
void destroySWFShapeArray(SWFArray array);
void destroySWFFillStyleArray(SWFArray array);
void destroySWFMovieClipArray(SWFArray array);

#endif /* MING_ARRAY_H */
