#include <signal.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc < 4 || strcmp(argv[1], "--help") ==0)
        usageErr("%s pid num-sigs sig-num [sin-num-2]", argv[0]);
    
    pid_t pid;
    int numSigs, sig, i;

    pid = getLong(argv[1], 0, "pid");
    numSigs = getInt(argv[2], GN_GT_0, "num-sigs");
    sig = getInt(argv[3], 0, "sig-num");

    printf("%s: sending signal %d to process %ld %d times\n",
                argv[0], sig, (long)pid, numSigs);

    for (i = 0; i < numSigs; i++) {
        if (kill(pid, sig) == -1)
            errExit("kill");
    }

    if (argc > 4) {
        sig = getInt(argv[4], 0, "nsig-num-2");
        if (kill(pid, sig) == -1)
            errExit("kill");
    }

    printf("%s: exiting\n", argv[0]);

    exit(EXIT_SUCCESS);
}