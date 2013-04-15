#ifndef _MYSOCKET_H_
#define _MYSOCKET_H_
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "myerror.h"
int listen_socket(in_addr_t ip,int backlog);
#endif
