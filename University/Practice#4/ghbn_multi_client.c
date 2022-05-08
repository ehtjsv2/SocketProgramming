#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

void error_handling(char* message);
void write_routine(int sock, char* buf);
void read_routine(int sock, char* buf);

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
	int i=0;
    char message[100];
    char* rcv_buf;
    char rcv_message[100];
	struct hostent* host;

    #define BUF_SIZE 100


    pid_t pid;

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
    else printf("conneted!");
    pid=fork();
    
    if(pid==0){
        printf("im child\n");
        write_routine(sock, message);}
    else
        read_routine(sock, message);
    close(sock);
    return 0;
}

void error_handling(char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

void write_routine(int sock, char *buf){
    while(1){
        scanf(" %s",buf);
        if(!strcmp(buf,"q\n")||!strcmp(buf,"Q\n")){
            shutdown(sock,SHUT_WR);
            return;
        }
        printf("write message :%s",buf);
        write(sock, buf, strlen(buf));
    }
}

void read_routine(int sock, char *buf){
    printf("read function\n");
    int str_len;
    while(1){
        str_len =read(sock,buf,16);
        printf("read : %s",buf);
        if(str_len == 0)
            return;
        buf[str_len]=0;
        printf("read : %s",buf);
    }
}