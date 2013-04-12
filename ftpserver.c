#include "mysocket.h"

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
	int listensocket = listen_socket(ip.s_addr,100);
	if(-1 == listensocket)
	{
		print_error_location();
		return -1;
	}
	//print addr 
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	bzero(&addr,addrlen);
	if(-1 == getsockname(listensocket,(struct sockaddr*)&addr,&addrlen))
	{
		print_error_location();
		return -1;
	}
	printf("ip addr is :%s,port:%d\n",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));

	return 0;

}
