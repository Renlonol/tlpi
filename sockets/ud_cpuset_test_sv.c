#define _GNU_SOURCE 
#include "ud_ucase.h"
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

static void *threadFunc(void *arg)
{
    (void*) arg;
    while(1)
	 sleep(1);
    return NULL;
}

void thread_create_test()
{
    pthread_t t1;
    int s, core;
    cpu_set_t cpuset;
    cpu_set_t cpuset_new;

    s = pthread_create(&t1, NULL, threadFunc, NULL);
    if (s != 0){
        printf("create thread failed.\n");
        return;
    }

    s = pthread_setname_np(t1, "cpuset_test");
    if ( s < 0)
    {
        printf("set thread name failed.\n");
        return;	
    }
    
    if (pthread_getaffinity_np(pthread_self(),sizeof(cpu_set_t), &cpuset))
    {
        printf("get thread affinity failed.\n");
        return;	
    }

    CPU_ZERO(&cpuset_new);
    for(core = 0; core < 8; core++)
    {
	 if (CPU_ISSET(core, &cpuset)) 
	 {
             printf("core %d in process affinity.\n", core);
	     continue; 
	 }
	 printf("set core %d to thread affinity\n", core);
	 CPU_SET(core, &cpuset_new);
    }

    if (pthread_setaffinity_np(t1, sizeof(cpuset_new), &cpuset_new))
    {
        printf("set thread affinity failed.\n");
        return;	
    }
    
    
}

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr, claddr;
    int sfd, j;
    ssize_t numBytes;
    socklen_t len;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1)
        errExit("socket");

    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
        errExit("remove-%s", SV_SOCK_PATH);

    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) - 1);

    if (bind(sfd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) == -1)
        errExit("bind");

    for (;;) {
        len = sizeof(struct sockaddr_un);
        numBytes = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &claddr, &len);
        if (numBytes == -1)
            errExit("recvfrom");

        printf("Server receive %ld bytes from %s\n", (long) numBytes, claddr.sun_path);

        for (j = 0; j < numBytes; j++) {
            buf[j] = toupper(buf[j]);
        }

        if (sendto(sfd, buf, numBytes, 0, (struct sockaddr *) &claddr, len) != numBytes)
            errExit("sendto");

	thread_create_test();
    }

    return 0;
}
