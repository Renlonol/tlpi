#include <fcntl.h>
#include "tlpi_hdr.h"

#define LINE_SIZE_MAX 129

int main(int argc, char *argv[])
{
    int fd;
    ssize_t numRead;
    ssize_t numWrite;
    char line[LINE_SIZE_MAX];

    fd = open("/proc/sys/kernel/pid_max", (argc > 1) ? O_RDWR : O_RDONLY);
    if (fd == -1)
        errExit("open");
    
    numRead = read(fd, line, sizeof(line));
    if (numRead == -1)
        errExit("read");
    
    if (argc > 1)
        printf("Old value: ");
    printf("%.*s", (int)numRead, line);

    if (argc > 1) {
        numWrite = write(fd, argv[1], strlen(argv[1]));
        if (numWrite != strlen(argv[1]))
            fatal("write");

        system("echo /proc/sys/kernel/pid_max mow contains "
                "`cat /proc/sys/kernel/pid_max`");
    }

    return 0;
}