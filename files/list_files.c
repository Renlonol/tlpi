#include <dirent.h>
#include "tlpi_hdr.h"

static void listFiles(const char *dirpath)
{
    DIR *dirPtr;
    struct dirent *direntPtr;
    Boolean isCurrent;

    isCurrent = strcmp(dirpath, ".") == 0;

    dirPtr = opendir(dirpath);
    if (dirpath == NULL)
        errExit("opendir");
    
    errno = 0;
    while ((direntPtr = readdir(dirPtr)) != NULL) {
        if (strcmp(direntPtr->d_name, ".") == 0 || strcmp(direntPtr->d_name, "..") == 0)
            continue;
        if (!isCurrent)
            printf("%s/", dirpath);
        printf("%s\n", direntPtr->d_name);
    }

    if (errno != 0)
        errExit("readdir");

    if (closedir(dirPtr) == -1)
        errMsg("closedir");
}


int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [dir...]\n", argv[0]);
    
    if (argc == 1)
        listFiles(".");
    else
        for (argv++; *argv; argv++)
            listFiles(*argv);

    return 0;
}