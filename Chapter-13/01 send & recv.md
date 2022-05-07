## What is send & recv
> * 리눅스기반에서 이때까지 fd끼리 입출력에서 write와 read를 써왔다
> * send & recv는 그것들과는 달리 옵션을 추가할 수 있다. 옵션매개변수에 0을하면 wrtie와 read와 같다.

## Option
![image](https://user-images.githubusercontent.com/79188587/167240924-06656d03-2746-47f3-a82f-b1827701a271.png)
> * MSG_PEEK는 스택 과 큐를 공부할 때 peek()과 같다고 생각하면된다. 데이터를 받아오고 삭제하지않고 그대로 INPUT_BUFFER에 남아있다.
> * MSG_DONTWAIT는 read같은 경우는 블로킹 상태에 빠질 수 있지만 recv에서 이 옵션을 넣어주면 Input_Buffer에 값이없으면 블로킹을 벗어난다.

## CODE
> * recv 코드만 올리겠다. (send 코드는 write로 "123"을 연결된 소켓에게 전송하는 코드이다)
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30
void error_handling(char *message) // error처리 함수
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc, char *argv[])
{
    int acpt_sock, recv_sock;  
    struct sockaddr_in acpt_adr, recv_adr;
    int str_len, state;
    socklen_t recv_adr_sz;
    char buf[BUF_SIZE];
    if(argc!=2)
    {
        printf("Usage: %s<prot>\n",argv[0]);
        exit(1);
    }

    acpt_sock = socket(PF_INET, SOCK_STREAM, 0); // 서버소켓과 같다
    memset(&acpt_adr, 0, sizeof(acpt_adr)); 
    acpt_adr.sin_family = AF_INET;
    acpt_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    acpt_adr.sin_port = htons(atoi(argv[1]));

    if(bind(acpt_sock, (struct sockaddr*)&acpt_adr, sizeof(acpt_adr))==-1)
        error_handling("bind() error!");
    listen(acpt_sock, 5);

    recv_adr_sz = sizeof(recv_adr);
    recv_sock = accept(acpt_sock, (struct sockaddr*)&recv_adr, &recv_adr_sz);   // send 소켓과 연결

    while(1)
    {
        str_len = recv(recv_sock, buf, sizeof(buf)-1,MSG_PEEK|MSG_DONTWAIT);    
        if(str_len>0) break;
    }
    buf[str_len] = 0;
    printf("Buffering %d bytes: %s \n", str_len, buf);

    str_len = recv(recv_sock, buf, sizeof(buf)-1,0);

    buf[str_len] = 0;
    printf("Read again: %s\n",buf);
    close(acpt_sock);
    close(recv_sock);
    return 0;
}

```
