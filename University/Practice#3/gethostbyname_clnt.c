#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

void error_handling(char* message);

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
	int i=0;
    char message[100];
    char* rcv_buf;
    char rcv_message[100];
	struct hostent* host;
	if(argc!=3)
	{
		printf("Usage: %s <addr>\n", argv[0]);
		exit(1);
	}
    sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock==-1)
        error_handling("sock error");
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        error_handling("connect() error!");
    while(1){
        printf("Enter a host name(q to quit):");
        scanf(" %s",message);
        if(((strcmp(message,"q"))==0) || ((strcmp(message,"quit")==0)))break;
        write(sock,message,strlen(message));
        read(sock,rcv_message,16);
        printf("%s\n",rcv_message);
    }
    close(sock);
}

void error_handling(char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}