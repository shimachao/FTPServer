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
int tcpServerSocket(in_addr_t ip,in_port_t port,struct sockaddr_in *clientaddr);

#endif
