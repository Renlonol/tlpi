
//#define _POSIX_C_SOURCE 199309
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "itimerspec_from_str.h"

void itimerspecFromStr(char *str, struct itimerspec *tsp)
{
    char *cptr, *sptr;

    char *tmp_str = strdup(str);

    cptr = strchr(tmp_str, ':');
    if (cptr != NULL)
        *cptr = '\0';

    sptr = strchr(tmp_str, '/');
    if (sptr != NULL)
        *sptr = '\0';

    tsp->it_value.tv_sec = atoi(tmp_str);
    tsp->it_value.tv_nsec = sptr ? atoi(sptr + 1) : 0;

    if (!cptr) {
        tsp->it_interval.tv_sec = 0;
        tsp->it_interval.tv_nsec = 0;
    } else {
        sptr = strchr(cptr + 1, '/');
        if (sptr)
            *sptr = '\0';
        tsp->it_interval.tv_sec = atoi(cptr + 1);
        tsp->it_interval.tv_nsec = sptr ? atoi(sptr + 1) : 0;
    }

    free(tmp_str);
}