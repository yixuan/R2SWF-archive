#include "libming.h"

char* __my__strdup (const char *s)
{
    char *p = malloc(strlen(s) + 1);
    if(p) { strcpy(p, s); }
    return p;
}

