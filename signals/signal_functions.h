#ifndef _SIGNAL_FUNCTIONS_H
#define _SIGNAL_FUNCTIONS_H
#include <signal.h>
#include "tlpi_hdr.h"

void printSigset(FILE *f, const char * prefix, sigset_t *sigset);

#endif