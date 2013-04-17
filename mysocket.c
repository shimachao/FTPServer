#include "mysocket.h"
int listen_socket(in_addr_t ip,int backlog)
{
	int listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(-1 == listenfd)
	{
		print_error_location();
		perror("tcpServerSocket: create socket error!");
		return -1;
	}
	//bind ip,let sys choose a port for us.
	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ip;
	if(-1 == bind(listenfd,(struct sockaddr*)&addr,sizeof(addr)))
	{
		print_error_location();
		perror("bind error!");
		return -1;
	}
	//listen...
	if(listen(listenfd,backlog) == -1)	
	{
		print_error_location();
		perror("tcpServerSocket: listen error");
		return -1;
	}
	return listenfd;
}

