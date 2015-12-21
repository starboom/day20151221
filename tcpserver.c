#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	struct sockaddr_in Addr,PeerAddr;

	Addr.sin_family = PF_INET;
	Addr.sin_port   = htons(1234);
	Addr.sin_addr.s_addr = inet_addr("192.168.1.3");

	int SeverSocket = socket(PF_INET,SOCK_STREAM,0);
	if(SeverSocket == -1)
	{
		perror("SeverSocket");
	}

	int BindSocket = bind(SeverSocket,(struct sockaddr *)&Addr,sizeof(Addr));
	if(BindSocket == -1)
	{
		perror("BindSocket");
	}
	int ListenSocket = listen(SeverSocket,10);
	if(ListenSocket == -1)
	{
		perror("ListenSocket");
	}
	socklen_t PeerAddrLen = sizeof(PeerAddr);
	int ClientSocket = accept(SeverSocket,(struct sockaddr *)&PeerAddr,&PeerAddrLen);
	if(ClientSocket == -1)
	{
		perror("ClientSocket");
	}

	char buf[1024];
	memset(buf,sizeof(buf),0);

	while(1)
	{
		read(ClientSocket,buf,sizeof(buf));
		printf("%s\n",buf );

		memset(buf,sizeof(buf),0);
	}

	return 0;
}
