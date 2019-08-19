#include <time.h>
#include <sys/time.h>
#include <locale.h>
#include "tlpi_hdr.h"

#define SECONDS_IN_TROPICAL_YEAR (364.24219 * 24 * 60 *60)

int main()
{
    time_t t;
    struct timeval tv;


    t = time(NULL);
    printf("Seconds since Epoch(1.1.1970): %ld", (long)t);
    printf(" (about %6.3f years)\n", t / SECONDS_IN_TROPICAL_YEAR);

    if (gettimeofday(&tv, NULL) == -1)
        errExit("gettimeofday");
    printf("gettimeofday() returned %ld secs, %ld microsecs\n",
                (long)tv.tv_sec, (long)tv.tv_usec);
    return 0;
}
