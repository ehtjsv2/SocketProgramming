#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

void error_handling(char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

#define BUF_SIZE 100

int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_size;
    char message[BUF_SIZE];
    int str_len;
    int i;
	struct hostent* host;
	if(argc!=2)
	{
		printf("Usage: %s <addr>\n", argv[0]);
		exit(1);
	}
    serv_sock=socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock==-1)
        error_handling("socket() error!");
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));
    if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
        error_handling("bind error!");
    if(listen(serv_sock,5)==-1)
        error_handling("listen() error!");
    clnt_adr_size=sizeof(clnt_adr);
    clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_adr, &clnt_adr_size);
    if(clnt_sock==-1)
        error_handling("accept() error!");
    else printf("new client connected\n");
    while(1){
        str_len=read(clnt_sock,message,BUF_SIZE-1);
        if(str_len==0)break;
        host=gethostbyname(message);
        if(host==NULL)
            write(clnt_sock,"gethost..error",sizeof("gethost..error"));
        else {
            write(clnt_sock,inet_ntoa(*(struct in_addr*)host->h_addr_list[0]), 16);
        }
    }
    printf("client disconnected...\n");
    close(clnt_sock);
    close(serv_sock);
}
