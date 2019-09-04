#define _BSD_SOURCE  /* Get major() and minor() from <sys/types>*/
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "file_perms.h"
#include "tlpi_hdr.h"


static void
displayStatInfo(const struct stat *sb)
{
    printf("File type:              ");
    switch (sb->st_mode & S_IFMT)
    {
        case S_IFREG:   printf("regular file\n");         break;
        case S_IFDIR:   printf("directory\n");            break;
        case S_IFCHR:   printf("character device\n");     break;
        case S_IFBLK:   printf("block device\n");         break;
        case S_IFLNK:   printf("symbolic link\n");        break;
        case S_IFIFO:   printf("FIFO or pipe\n");         break;
        case S_IFSOCK:  printf("socket\n");               break;
        default:        printf("unknown file type?\n");   break;
    }
}

int main(int argc, char *argv[])
{
    struct stat sb;
    Boolean statLink;   /* True for if "-l" specified (use lstat)*/
    int fname_index;

    statLink = (argc > 1) && strcmp(argv[1], "-l") == 0;

    fname_index = statLink ? 2 : 1;

    if (fname_index >= argc || (argc > 1 && strcmp(argv[1], "--help") == 0))
        usageErr("%s [-l] file\n"
                    "       -l = use lstat() instead of stat()\n", argv[0]);
    
    if (statLink) {
        if (lstat(argv[fname_index], &sb) == -1)
            errExit("lstat");
    } else {
        if (stat(argv[fname_index], &sb) == -1)
            errExit("stat");
    }

    displayStatInfo(&sb);

    return 0;
}