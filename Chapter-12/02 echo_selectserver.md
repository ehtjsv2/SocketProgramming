# CODE

```c
  #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <sys/time.h>
    #include <sys/select.h>

    #define BUF_SIZE 100
void error_handling(char *buf);

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock; 
    struct sockaddr_in serv_adr, clnt_adr;
    struct timeval timeout; //timeout 변수
    fd_set reads, cpy_reads; // fd_set 변수

    socklen_t adr_sz;
    int fd_max, str_len, fd_num, i;
    char buf[BUF_SIZE];
    if(argc!=2){
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // 서버 소켓
    memset(&serv_adr, 0, sizeof(serv_adr)); 
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))== -1) // bind
        error_handling("bind() error!");
    if(listen(serv_sock,5)==-1) // listen
        error_handling("listen() error!");
        
    FD_ZERO(&reads); // reads의 모든 비트를 0으로 초기화
    FD_SET(serv_sock, &reads);  // fd_set변수 reads에 서버 소켓등록
    fd_max = serv_sock; // 적어도 fd_max는 serv_sock 까지 검사해야하므로 fd_max를 serv_sock으로 설정(아마 socket이 순차적인 int형으로 형성되나보다)

    while(1)
    {
        cpy_reads=reads;  // select가 초기화하기때문에 복사
        timeout.tv_sec = 5; //timeout 5초
        timeout.tv_usec =5000;

        if((fd_num=select(fd_max+1, &cpy_reads, 0, 0, &timeout))==-1) // fd_max+1개의 파일 디스크립터를 관찰, cpy_reads의 수신데이터변화에집중
            break; // error시
        if(fd_num==0)
            continue; // timeout시

        for(i=0; i<fd_max+1;i++){ // 변화발견하면(connect요청이 왔을 시에)
            if(FD_ISSET(i, &cpy_reads)) // cpy_reads의 몇번째가 변화가있는것인지
            {
                if(i==serv_sock) // 변화있는곳이 serv_sock이 맞는지
                {
                    adr_sz=sizeof(clnt_adr);  
                    clnt_sock=
                        accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz); // accept과정
                    FD_SET(clnt_sock, &reads); // accept한 clnt_sock을 fd_set변수 reads에 추가
                    if(fd_max<clnt_sock)  //  clnt_sock도 다음 검사항목에 들어가야하므로 
                        fd_max = clnt_sock;
                    printf("connected client: %d \n",clnt_sock);
                }
                else{
                    str_len = read(i, buf, BUF_SIZE); //serv_sock의 변화가아닐 경우-> clnt_sock의 변화이다.
                    if(str_len == 0){ // 연결이 끊기면 read는 0을 반환한다.
                        FD_CLR(i, &reads); // 연결끊겼으므로 파일디스크립터 제거
                        close(i); // 연결해제
                        printf("closed client: %d \n", i);
                    }
                    else{
                        write(i, buf, str_len); // 연결되어있으면 그대로 clnt_sock에 문자열 반환
                    }
                }
            }
        }
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *buf){
    fputs(buf, stderr);
    fputs('\n',stderr);
    exit(1);
}
```
