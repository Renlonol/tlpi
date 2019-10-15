#define _GNU_SOURCE /* Get strsignal() declaration from <string.h> */
#include <string.h>
#include <sys/wait.h>
#include "print_wait_status.h"
#include "tlpi_hdr.h"

void printWaitStatus(const char *msg, int status)
{
    if (msg)
        printf("%s", msg);
    
    if (WIFEXITED(status)) {
        //child exit nornally
        printf("Child exited, status=%d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Child killed by signal %d (%s)",
                WTERMSIG(status), strsignal(WTERMSIG(status)));
#ifdef WCOREDUMP
        if (WCOREDUMP(status))
            printf(" (core dumped)");
#endif
        printf("\n");
    } else if (WIFSTOPPED(status)) {
        printf("Child stopped by signal %d (%s)\n",
                WSTOPSIG(status), strsignal(WSTOPSIG(status)));
#ifdef WIFCONTINUED
    } else if (WIFCONTINUED(status)) {
        printf("Child continued\n");
#endif
    } else { /* should never happen */
        printf("what happened to this child? (status=%x)\n",
                (unsigned int) status);
    }
}