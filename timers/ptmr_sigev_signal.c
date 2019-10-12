#define _POSIX_C_SOURCE 199309
#include <signal.h>
#include <time.h>
#include "tlpi_hdr.h"
#include "curr_time.h"
#include "itimerspec_from_str.h"

#define TIMER_SIG SIGRTMAX

static void handler(int sig, siginfo_t *si, void *uc)
{
    timer_t *tidptr = si->si_value.sival_ptr;

    printf("[%s] Got signal %d\n", currTime("%T"), sig);
    printf("    *sival_ptr         = %ld\n", (long) *tidptr);
    printf("    timer_getoverrun() = %d\n", timer_getoverrun(*tidptr));
}

int main(int argc, char *argv[])
{
    struct sigevent sev;
    struct itimerspec ts;
    struct sigaction sa;
    timer_t *tidlist;
    int i;

    if (argc < 2)
        usageErr("%s secs[nsecs]\n", argv[0]);

    tidlist = calloc(argc - 1, sizeof(timer_t));
    if (tidlist == NULL)
        errExit("calloc");

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(TIMER_SIG, &sa, NULL) == -1)
        errExit("sigaction");

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = TIMER_SIG;

    for (i = 0; i < argc - 1; i++)
    {
        itimerspecFromStr(argv[i+1], &ts);

        sev.sigev_value.sival_ptr = &tidlist[i];

        if (timer_create(CLOCK_REALTIME, &sev, &tidlist[i]) == -1)
            errExit("timer creat");
        printf("Timer ID: %ld (%s)\n", (long)tidlist[i], argv[i+1]);

        if (timer_settime(tidlist[i], 0, &ts, NULL) == -1)
            errExit("timer set");
    }

    for (;;)
        pause();

    return 0;
}
