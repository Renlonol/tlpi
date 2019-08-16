#include "tlpi_hdr.h"

#define MAX_ALLOCS 1000000

int main(int argc, char* argv[])
{
    char* ptr[MAX_ALLOCS];
    int freeStep, freeMin, freeMax, blockSize, numAllocs;
    int i;

    if (argc < 3 || strcmp(argv[1], "--help") ==0)
        usageErr("%s num-allocs block-size [step [min [max]]]\n", argv[0]);

    numAllocs = getInt(argv[1], GN_GT_0, "num-allocs");

    if (numAllocs > MAX_ALLOCS)
        cmdLineErr("num-alloc > %d\n", MAX_ALLOCS);

    blockSize = getInt(argv[2], GN_GT_0 | GN_ANY_BASE, "block-size");

    freeStep = (argc > 3) ? getInt(argv[3], GN_GT_0, "freeStep") : 1;
    freeMin  = (argc > 4) ? getInt(argv[4], GN_GT_0, "freeMin") : 1;
    freeMax  = (argc > 5) ? getInt(argv[5], GN_GT_0, "freeMax") : numAllocs;

    if (freeMax > numAllocs)
        cmdLineErr("free-max > num-allocs(%d)", numAllocs);
    
    printf("Initial program break:          %10p\n", sbrk(0));

    printf("Allocating %d*%d bytes\n", numAllocs, blockSize);
    for(i = 0; i < numAllocs; i++)
    {
        ptr[i] = malloc(blockSize);
        if (ptr[i] == NULL)
            errExit("Allocate failed at %d\n", i);
    }

    printf("Program break now:              %10p\n", sbrk(0));

    printf("Freeing blocks from %d to %d in step of %d\n", freeMin, freeMax, freeStep);
    for(i = freeMin - 1; i < freeMax; i+=freeStep)
    {
        free(ptr[i]);
    }

    printf("After free(), program break is: %10p\n", sbrk(0));

    return 0;
}