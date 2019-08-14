#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    int fd, flags;
    mode_t filePerms;
    off_t offset;

    int i, j;
    size_t len, numRead, numWrite;
    char *buf = NULL;

    if (argc < 3 || strcmp(argv[1], "--help") ==0)
        usageErr("%s file {r<length>|R<length>|w<string>|S<offset>}...\n", argv[0]);

    flags    = O_CREAT | O_RDWR;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;
    fd = open(argv[1], flags, filePerms);
    if (fd == -1)\
        errExit("open file %s", argv[1]);

    for (i = 2; i < argc; i++)
    {
        switch(argv[i][0]) {
            case 'r':
            case 'R':
                len = getLong(&argv[i][1], GN_ANY_BASE, argv[i]);
                buf = malloc(len);
                if (buf == NULL)
                    errExit("malloc");
                
                numRead = read(fd, buf, len);
                if (numRead == -1)
                    errExit("read");
                
                if (numRead == 0)
                    printf("%s: end-of-file\n",argv[i]);
                else {
                    printf("%s: ", argv[i]);
                    for (j = 0; j < numRead; j++) {
                        if (argv[i][0] == 'r')
                            printf("%c", buf[j]);
                        else
                            printf("%02x ", buf[j]);
                    }
                    printf("\n");
                }
                free(buf);
                break;
            case 'w':
                numWrite = write(fd, &argv[i][1], strlen(&argv[i][1]));
                if (numWrite == -1)
                    errExit("write");
                
                printf("%s: wrote %ld bytes \n", argv[i], (long)numWrite);
                break;
            case 's':
                offset = getLong(&argv[i][1], GN_ANY_BASE, argv[i]);
                if (lseek(fd, offset, SEEK_SET) == -1)
                    errExit("lseek");
                printf("%s: seek ok\n", argv[i]);
                break;
            default:
                cmdLineErr("Args must start with [rRws]: %s\n", argv[i]);
        }
    }

    return 0;
}