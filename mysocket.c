#include "mysocket.h"
int tcpServerSocket(in_addr_t ip,in_port_t port,struct sockaddr_in *clientaddr)
{
	if(NULL == clientaddr)
	{
		perror("tcpServerSocket: clientaddr is null!");
		return -1;
	}
	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == listenfd)
	{
		perror("tcpServerSocket: create socket error!");
		return 0;
	}
	//bind...
	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(ip);
	servaddr.sin_port = htons(port);

	if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
	{
		perror("tcpServerSocketbind error!");
		return -1;
	}
	//listen...
	if(listen(listenfd,5) == -1)
	{
		perror("tcpServerSocket: listen error");
		return -1;
	}
	//accept..
	bzero(clientaddr,sizeof(struct sockaddr_in));
	socklen_t len = sizeof(struct sockaddr_in);
	int acceptfd = accept(listenfd,(struct sockaddr*)clientaddr,&len);
	if(-1 == acceptfd)
	{
		perror("tcpServerSocket: accept error!\n");
		return -1;
	}
	close(listenfd);
	return acceptfd;
}

