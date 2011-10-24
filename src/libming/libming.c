#include "libming.h"

char* __my__strdup (const char *s)
{
    size_t len = strlen (s) + 1;
    void *snew = malloc (len);
    if (snew == NULL)
        return NULL;

    return (char *) memcpy (snew, s, len);
}
