#include "ming-array.h"

SWFArray newSWFArray(int initialSize)
{
    SWFArray array = (SWFArray) malloc(sizeof(struct SWFArray_s));
    if(!array)
    {
        SWF_error("fail to allocate memory");
        return array; /* should not get here */
    }
    array->len = 0;
    array->alloc_len = initialSize;
    array->data = (SWFObject *) calloc(array->alloc_len, sizeof(SWFObject));
    if(!array->data)
    {
        SWF_error("fail to allocate memory");
        return array; /* should not get here */
    }

    return array;
}

void SWFArray_append(SWFArray array, SWFObject obj)
{
    if(!array) return;
    if(array->len + 1 > array->alloc_len)
    {
        array->alloc_len *= 2;
        array->data = (SWFObject *) realloc(array->data, array->alloc_len * sizeof(SWFObject));
    }
    array->data[array->len] = obj;
    array->len++;
}

void destroySWFShapeArray(SWFArray array)
{
    int i;

    if(!array) return;
    for(i = 0; i < array->len; i++)
    {
        if(array->data[i]) destroySWFShape((SWFShape) array->data[i]);
    }
    if(array->data) free(array->data);
    if(array) free(array);
}

void destroySWFFillStyleArray(SWFArray array)
{
    int i;

    if(!array) return;
    for(i = 0; i < array->len; i++)
    {
        if(array->data[i]) destroySWFFillStyle((SWFFillStyle) array->data[i]);
    }
    if(array->data) free(array->data);
    if(array) free(array);
}

void destroySWFMovieClipArray(SWFArray array)
{
    int i;

    if(!array) return;
    for(i = 0; i < array->len; i++)
    {
        if(array->data[i]) destroySWFMovieClip((SWFMovieClip) array->data[i]);
    }
    if(array->data) free(array->data);
    if(array) free(array);
}
