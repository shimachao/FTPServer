#include "recv_file.h"
void *file_recv(void *arg)
{
	pthread_detach(pthread_self());
	PAR_TO_THREAD *p = (PAR_TO_THREAD*)arg;
	int commandfd = p->acceptfd;
	//create server data socket
	struct in_addr ip;
	if(0 == inet_aton("121.199.24.119",&ip))
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
	memcpy(pbuf,&(addr.sin_addr.s_addr),sizeof(in_addr_t));
	memcpy(pbuf+sizeof(in_addr_t),&(addr.sin_port),sizeof(in_port_t));
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
	//TODO-->用户验证，证明是特定用户发来的数据连接
	//create a thread for data channel	
	pthread_t tid;
	PAR_TO_DATACHANNEL *arg2 = malloc(sizeof(PAR_TO_DATACHANNEL));
	arg2->datafd = datafd;
	if(0 != pthread_create(&tid,NULL,data_channel,(void*)arg2))
	{
		print_error_location();
		perror("create data channel fialed!");
		close(datafd);
		close(listenfd);
		close(commandfd);
	}	
	return NULL;
}

void *data_channel(void *arg)
{
	pthread_detach(pthread_self());
	
	PAR_TO_DATACHANNEL *p =(PAR_TO_DATACHANNEL*) arg;
	int datafd = p->datafd;
	free(p);
	p = NULL;
	FILE *fp = fopen("/root/chao/user_video/test.mp4","wb");	
	if(NULL == fp)
	{
		print_error_location();
		perror("fopen failed!");
		close(datafd);
		return NULL;
	}

	printf("recving data...\n");
	char buf[1024];
	ssize_t readlen = 0;
	while((readlen = read(datafd,(void*)buf,1024)) != 0)
	{
		if(readlen == -1)
		{
			print_error_location();
			perror("read data from datafd error!\n");
			break;
		}
		fwrite(buf,sizeof(char),readlen,fp);
	}

	fclose(fp);
	close(datafd);
	printf("rececive data over!\n");

	return NULL;
}
