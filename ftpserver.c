#include "mysocket.h"
#include "mypthread.h"
#include <stdlib.h>
int main()
{
	//waiting for transfer requsets from clients
	struct in_addr ip;
	if(0 == inet_aton("192.168.1.222",&ip))
	{
		print_error_location();
		perror("ip is wrong!\n");
		return -1;
	}
	int listenfd = listen_socket(ip.s_addr,100);
	if(-1 == listenfd)
	{
		print_error_location();
		return -1;
	}
	//print addr 
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	bzero(&addr,addrlen);
	if(-1 == getsockname(listenfd,(struct sockaddr*)&addr,&addrlen))
	{
		print_error_location();
		return -1;
	}
	printf("ip addr is :%s,port:%d\n",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));

	//accept a connect requset 
	while(1)
	{
		int acceptfd = accept(listenfd,NULL,NULL);
		if(-1 == acceptfd)
		{
			print_error_location();
			perror("accept wrong!\n");
			continue;
		}
		//create a thread to recv file from client
		pthread_t tid;
		PAR_TO_THREAD *p = (PAR_TO_THREAD*)malloc(sizeof(PAR_TO_THREAD));
		int err = pthread_create(&tid,NULL,file_recv,(void*)p);
		if(0 != err)
		{
			perror("create thread faild\n");
			continue;
		}

	}

	return 0;

}
