## CODE(Sender)
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TTL 64
#define BUF_SIZE 30
void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc, char *argv[])
{
    int send_sock;
    struct sockaddr_in mul_adr;
    int time_live=TTL;
    FILE *fp;
    char buf[BUF_SIZE];

    if(argc!=3){
        printf("Usage : %s <GroupIP> <prot>\n",argv[0]);
        exit(1);
    }

    send_sock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&mul_adr,0,sizeof(mul_adr));
    mul_adr.sin_family = AF_INET;
    mul_adr.sin_addr.s_addr = inet_addr(argv[1]);
    mul_adr.sin_port = htons(atoi(argv[2]));

    setsockopt(send_sock, IPPROTO_IP,IP_MULTICAST_TTL, (void*)&time_live,sizeof(time_live));
    if((fp=fopen("news-1.txt","r"))==NULL)
        error_handling("fopen() error!");

    while(!feof(fp))
    {
        fgets(buf,BUF_SIZE,fp);
        sendto(send_sock, buf, strlen(buf), 0, (struct sockaddr*)&mul_adr,sizeof(mul_adr));
        sleep(1);
    }
    fclose(fp);
    close(send_sock);
    return 0;
}
```
## CODE(Receiver)
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc, char *argv[])
{
    int recv_sock;
    int str_len;
    char buf[BUF_SIZE];
    struct sockaddr_in adr;
    struct ip_mreq join_adr;

    if(argc!=3){
        printf("Usage : %s <GroupIP> <port>\n",argv[0]);
        exit(1);
    }

    recv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&adr, 0, sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = htonl(INADDR_ANY);
    adr.sin_port = htons(atoi(argv[2]));

    if(bind(recv_sock, (struct sockaddr*)&adr,sizeof(adr))==-1)
        error_handling("bind() error");

        join_adr.imr_multiaddr.s_addr=inet_addr(argv[1]);
        join_adr.imr_interface.s_addr=htonl(INADDR_ANY);
        setsockopt(recv_sock, IPPROTO_IP,IP_ADD_MEMBERSHIP,(void*)&join_adr,sizeof(join_adr));

        while(1)
        {
            str_len = recvfrom(recv_sock, buf, BUF_SIZE-1,0,NULL,0);
            if(str_len<0)
                break;
            buf[str_len]=0;
            fputs(buf,stdout);
        }
        close(recv_sock);
        return 0;
}
```

