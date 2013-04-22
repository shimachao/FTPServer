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

typedef struct PAR_TO_DATACHANNEL{
	int datafd;
}PAR_TO_DATACHANNEL;

void *file_recv(void *arg);
void *data_channel(void *arg);
#endif
