#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>

void error_handling(char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

void read_childproc(int sig){
    pid_t pid;
    int status;
    pid=waitpid(-1, &status, WNOHANG);
    printf("removed proc id: %d \n",pid);
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

    pid_t pid;
    struct sigaction act;

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

    while(1)
    {
        clnt_adr_size=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_adr, &clnt_adr_size);
        if(clnt_sock==-1)
            continue;
        else
            puts("new client connected...");
        pid=fork();
        if(pid ==-1){
            close(clnt_sock);
            continue;
        }
        if(pid==0){
            close(serv_sock);
            while((str_len=read(clnt_sock,message,BUF_SIZE)-1)!=0){
                host=gethostbyname(message);
                if(host==NULL){
                    write(clnt_sock,"gethost..error",strlen("gethost..error"));
                }
                else{
                    write(clnt_sock,inet_ntoa(*(struct in_addr*)host->h_addr_list[0]), 16);
                }   
            }
            close(clnt_sock);
            puts("client disconneted...");
            return 0;
        }
        else
            close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}
 