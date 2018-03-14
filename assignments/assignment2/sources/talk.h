#ifndef TALK_H
#define TALK_H
#include "linux/kernel.h"
#include "linux/unistd.h"

static char * message = NULL;
extern int sys_get(char *, int);
extern int sys_put(char *, int );
extern int sys_length(int *);
#endif
