#ifndef _MY_THREAD_H_
#define _MY_THREAD_H_
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "mysocket.h"
#include "myerror.h"
typedef struct PAR_TO_THREAD{
	int acceptfd;
}PAR_TO_THREAD;
void *file_recv(void *arg);

#endif
