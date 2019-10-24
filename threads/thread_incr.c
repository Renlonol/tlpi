#include <pthread.h>
#include "tlpi_hdr.h"
#include "curr_time.h"

static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void *threadFunc(void *arg)
{
    int loops = *((int *) arg);
    int j, s;

    for(j = 0; j < loops; j++)
    {
        s = pthread_mutex_lock(&mtx);
        if( s != 0)
            errExitEN(s, "pthread_mutex_lock");
        
        glob++;

        s = pthread_mutex_unlock(&mtx);
        if (s != 0)
            errExitEN(s, "pthread_mutex_unlock");
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;

    loops = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-loops") : 10000000;

    printf("%s start\n", currTime("%T"));

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0)
        errExitEN(s, "pthread_create t1");

    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0)
        errExitEN(s, "pthread_create t2");

    s = pthread_join(t1, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join t1");

    s = pthread_join(t2, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join t1");
    
    printf("%s end\n", currTime("%T"));
    printf("glod = %d\n", glob);

    return 0;
}