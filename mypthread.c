#include "mypthread.h"
void *file_recv(void *arg)
{
	PAR_TO_THREAD *p = (PAR_TO_THREAD*)arg;
	int commandfd = p->acceptfd;
	//create server data socket
	struct in_addr ip;
	if(0 == inet_aton("192.168.222",&ip))
	{
		print_error_location();
		perror("ip is wrong!\n");
		return NULL;
	}
	int listenfd = listen_socket(ip.s_addr,1);
	if(-1 == listenfd)
	{
		print_error_location();
		perror("creat listen socket for datasocket fialed!\n");
		return NULL;
	}
	//get addr associated with listenfd which is the same as datasocket's addr.
	//and send it to client
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	bzero(&addr,addrlen);
	if(-1 == getsockname(listenfd,(struct sockaddr*)&addr,&addrlen))
	{
		print_error_location();
		perror("get locat data addr failed!\n");
		return NULL;
	}
	char *pbuf = (char*)malloc(sizeof(in_addr_t)+sizeof(in_port_t));
	bzero(pbuf,sizeof(in_addr_t)+sizeof(in_port_t));
	//send to client
	if(send(commandfd,pbuf,sizeof(in_addr_t)+sizeof(in_port_t),0) == -1)
	{
		perror("send addr fialed!");
		free(pbuf);
		return NULL;
	}
	free(pbuf);
	//accept data connection
	int datafd = accept(listenfd,NULL,NULL);
	if(-1 == datafd)
	{
		print_error_location();
		perror("data socket error!");
		return NULL;
	}
	//data channel connected,begin receive file data
	FILE *fp = fopen("/char/test.avi","wb");
	if(NULL == fp)
	{
		print_error_location();
		perror("fopen test.avr fialed!\n");
		close(datafd);
		close(listenfd);
		close(commandfd);
		return NULL;
	}
	char buf[1024];
	ssize_t readlen;
	while((readlen =read(datafd,(void*)buf,1024)) != 0)
	{
		if(readlen == -1)
		{
			print_error_location();
			perror("read data from datasocket error!\n");
			break;
		}
		fwrite(buf,sizeof(char),readlen,fp);
	}
	fclose(fp);
	close(datafd);
	close(listenfd);
	close(commandfd);
	return NULL;
}

