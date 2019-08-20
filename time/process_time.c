#include <time.h>
#include <sys/times.h>
#include <locale.h>
#include "tlpi_hdr.h"

void displayProcessTimes(const char *msg)
{
    struct tms t;
    clock_t clockTime;
    static long clockTicks = 0;

    if (msg != NULL)
        printf("%s\n", msg);

    if (clockTicks == 0) {
        clockTicks = sysconf(_SC_CLK_TCK);
        if (clockTicks == -1)
            errExit("sysconf");
    }

    clockTime = clock();
    if (clockTime == -1)
        errExit("clock");

    printf("    clock() returns: %ld clocks-per-sec (%.2f secs)\n",
            (long)clockTime, (double) clockTime / CLOCKS_PER_SEC);

    if (times(&t) == -1)
        errExit("times()");

    printf("    times() yields: user CPU=%.2f; system CPU: %.2f\n",
            (double) t.tms_utime / clockTicks, (double) t.tms_stime / clockTicks);
}

int main(int argc, char *argv[])
{
    int numCalls, i;

    printf("CLOCKS_PER_SEC=%ld    sysconf(_SC_CLK_TCK)=%ld\n\n",
            (long)CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));

    displayProcessTimes("At program start:");

    numCalls = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-Calls") : 100000000;
    for (i = 0; i < numCalls; i++)
        (void)getppid();

    displayProcessTimes("After getppid() loop:");

    return 0;
}