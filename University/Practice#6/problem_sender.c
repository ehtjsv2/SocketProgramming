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
    struct sockaddr_in mul_adr1, mul_adr2;
    int time_live=TTL;
    FILE *fp;
    char buf[BUF_SIZE];

    if(argc!=4){
        printf("Usage : %s <GroupIP> <prot> <port>\n",argv[0]);
        exit(1);
    }

    send_sock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&mul_adr1,0,sizeof(mul_adr1));
    mul_adr1.sin_family = AF_INET;
    mul_adr1.sin_addr.s_addr = inet_addr(argv[1]);
    mul_adr1.sin_port = htons(atoi(argv[2]));

    memset(&mul_adr2,0,sizeof(mul_adr2));
    mul_adr2.sin_family = AF_INET;
    mul_adr2.sin_addr.s_addr = inet_addr(argv[1]);
    mul_adr2.sin_port = htons(atoi(argv[3]));

    setsockopt(send_sock, IPPROTO_IP,IP_MULTICAST_TTL, (void*)&time_live,sizeof(time_live));
    if((fp=fopen("news-1.txt","r"))==NULL)
        error_handling("fopen() error!");

    while(!feof(fp))
    {
        fgets(buf,BUF_SIZE,fp);
        sendto(send_sock, buf, strlen(buf), 0, (struct sockaddr*)&mul_adr1,sizeof(mul_adr1));
        sendto(send_sock, buf, strlen(buf), 0, (struct sockaddr*)&mul_adr2,sizeof(mul_adr2));
        sleep(1);
    }
    fclose(fp);
    close(send_sock);
    return 0;
}