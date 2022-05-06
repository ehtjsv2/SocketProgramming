## Select란?
> * 한번에 여러개의 디스크립터를 관찰하기 위해 존재<br/>
> * 변화가 올때까지 대기하는 함수이다.<br/>

## 알아야하는 것들
> 1. fd_set (파일디스크립터 형 배열변수)
> 2. FD_ZERO (fd_set형 변수의 모든비트를 0으로 초기화)
> 3. FD_SET (fd_set형 변수에 전달된 파일 디스크립터 정보를 등록한다.)
> 4. FD_CLR (fd_set형 변수에서 전달된 파일 디스크립터 정보를 삭제한다.)
> 5. FD_ISSET (select함수의 호출결과를 확인하는 용도로사용, 전달된 파일 디스크립터에 변화된 정보가 있으면 양수반환)
> 6. struct timeval 변수 (select의 타임 아웃을 설정하기 위한것. timeout.tv_sec와 timeout.tv_usec를 설정해야한다.) 

# select()
> * int select(int maxfd, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timaval *timeout)
>   * maxfd - 검사 대상이 되는 파일 디스크립터의 수
>   * readset - 수신 데이터의 존재여부에 관심있는 파일 디스크립터
>   * writeset - 데이터의 전송 가능여부 에 관심있는 파일 디스크립터
>   * exceptset - 예외상황 발생여부에 관심있는 파일 디스크립터
>   * timeout - select함수가 무한정 블로킹에 빠지지않도록 타임아웃을 설정
>   * 반환값 - 오류는 -1, 타임아웃 시에는 0, 변화발생시 변화 발생한 파일디스크립터의 개수

## CODE
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    int first =0;
    fd_set reads, temps; // fd_set형 변수선언
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout; // timeout 변수선언
    
    FD_ZERO(&reads);    // fd_set형 변수 비트 0으로초기화
    FD_SET(0,&reads);   // fd_set형 변수 reads중 0(consol Standard Input)에 관심을 가지겠다는 것.
    timeout.tv_sec=0;   
    timeout.tv_usec=0;
    while(1){
        fflush(stdout);
        // select가 끝나고나면 변화가 생긴 파일 디스크립터위치를 제외한 모든비트는 0으로초기화 되기때문에
        // 원본을 유지하기위해 복사의 과정을 거치고 select에는 복사본을 넣는다.
        temps=reads;    
        result = select(1, &temps, 0, 0, &timeout); // 검사할 fd는 1개 temp의 수신데이터여부에 관심 timeout
        if(result == -1)
        {
            puts("select() error!");
            break;
        }
        else if(result == 0)
        {
            if(first==0)
            {
                first++;
                printf("what do you want to drink?: ");
                fflush(stdout);
            }
            else
            {
                puts("too late!! hurry up!");
                printf("what do you want to drink?: ");
                fflush(stdout);
            }
        }
        else{
            if(FD_ISSET(0,&temps))
            {
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                printf("ok, i wll serve you :%s",buf);
            }
        }
        // select후에는 밑에 변수의 값이 타임아웃이 발생하기 까지 남았던 시간으로 바뀌기 때문에 select후에 반복설정 하게 해주어야한다.
        timeout.tv_sec=5;
        timeout.tv_usec=0;
    }
}
```
