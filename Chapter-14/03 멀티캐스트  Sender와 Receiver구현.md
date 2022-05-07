## 배운점
> * 멀티캐스트는 방송의 개념이다 Receiver가 실행되지 않아도 혼자 sleep시간에 맞춰 전송중이다.
>   * 따라서 Receiver를 늦게 실행하면 데이터를 중간부터 받게 될 것이다.
> * bind는 서비스가 잘 찾아오게 주소를 부여하는 것이라 생각하면 된다.
>   * 따라서 UDP에서의 Sender는 보내기만 하면되므로 bind()를 하지않는다.
>   * 하지만 receiver는 sender가 찾아올 수 있어야하므로 bind()를 한다.
>   * 번외로 UDP 서버, 클라이언트에서는 서버는 bind()하고 client는 하지않았다. 서버에서 clinet에 전송할경우 수신할때 받은 client주소를 이용해서 전송했다.

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
    struct sockaddr_in mul_adr; // 데이터를 전송할 멀티캐스트의 주소를 담을 변수
    int time_live=TTL; // TTL을 위한 변수
    FILE *fp;   
    char buf[BUF_SIZE];

    if(argc!=3){
        printf("Usage : %s <GroupIP> <prot>\n",argv[0]);
        exit(1);
    }

    send_sock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&mul_adr,0,sizeof(mul_adr));
    mul_adr.sin_family = AF_INET;   // 데이터를 전송할 멀티캐스트의 주소를 설정
    mul_adr.sin_addr.s_addr = inet_addr(argv[1]);   // 콘솔에서 설정한 IP를 멀티캐스트의 IP주소로 할당
    mul_adr.sin_port = htons(atoi(argv[2]));    // 위와 동일

    setsockopt(send_sock, IPPROTO_IP,IP_MULTICAST_TTL, (void*)&time_live,sizeof(time_live)); // 소켓의 TTL정보를 지정
    if((fp=fopen("news-1.txt","r"))==NULL)  // 보낼 데이터가 담긴 txt파일을 읽기모드로 불러옴
        error_handling("fopen() error!");

    while(!feof(fp))    // 파일이 끝날때까지
    {
        fgets(buf,BUF_SIZE,fp); // 한줄씩 불러옴
        sendto(send_sock, buf, strlen(buf), 0, (struct sockaddr*)&mul_adr,sizeof(mul_adr)); //UDP기반이므로 sendto, 멀티캐스트 주소로 데이터전달
        sleep(1);   // 데이터전송의 시간간격을 두기 위함.
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

    if(bind(recv_sock, (struct sockaddr*)&adr,sizeof(adr))==-1) // 서비스가 잘찾오게 하기위해 주소는 부여해야한다.
        error_handling("bind() error");

        join_adr.imr_multiaddr.s_addr=inet_addr(argv[1]);   // 멀티캐스트의 주소 설정
        join_adr.imr_interface.s_addr=htonl(INADDR_ANY);    // 이 소켓이 속한 호스트의 IP주소(INADDR_ANY도 가능)
        setsockopt(recv_sock, IPPROTO_IP,IP_ADD_MEMBERSHIP,(void*)&join_adr,sizeof(join_adr));  // 멀티캐스트 그룹에 가입  

        while(1)
        {
            str_len = recvfrom(recv_sock, buf, BUF_SIZE-1,0,NULL,0);    // 주소지 알 필요없므로 NULL과 0을 삽입
            if(str_len<0)
                break;
            buf[str_len]=0;
            fputs(buf,stdout);
        }
        close(recv_sock);
        return 0;
}
```

