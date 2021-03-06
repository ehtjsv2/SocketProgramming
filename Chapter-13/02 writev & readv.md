## writev 와 readv 란??
> * 데이터의 송수신 효율성을 향상시키위해 사용 (함수의 호출횟수를 줄일 수 있기때문)
> * 데이터를 모아서 전송, 모아서 수신 기능의 함수이다.

## writev
```c
ssize_t writev(int filedes, const struct iovec * iov, int iovcnt);
```
>   * filedes - 전송할 목적지 파일 디스크립터
>   * iov - 구조체 iovec 배열 주소 값 전달
>   * iovcnt - iov의 배열의 길이정보 전달

## readv
```c
ssize_t readv(int filedes, const struct iovec, int iovcnt);
```
> * filedes - 수신할 파일 디스크립터
>  * iov - 구조체 iovec 배열 주소 값 전달
>  * iovcnt - iov의 배열의 길이정보 전달
 

## struct iovec
```c
struct iovec
{
  void *iov_base; // 버퍼의 주소정보
  size_t iov_len; // 버퍼의 크기정보
}
```

## CODE(writev)
```c
#include <stdio.h>
#include <sys/uio.h>

int main(int argc, char* argv[])
{
    struct iovec vec[2];
    char buf1[] = "ABCDEFG"; // 버퍼1
    char buf2[] = "1234567"; // 버퍼2
    int str_len;

    vec[0].iov_base = buf1; // iovec vec[0]의 버퍼 주소 설정
    vec[0].iov_len = 3; // iovec vec[0]의 버퍼 크기 설정
    vec[1].iov_base = buf2; 
    vec[1].iov_len = 4;

    str_len = writev(1, vec, 2); // 1(console 의 standard output 디스크립터), vec버퍼, 크기2
    puts("");
    printf("Write bytes: %d\n",str_len);
}
```
## 출력
![image](https://user-images.githubusercontent.com/79188587/167243254-fea9a944-9456-4912-affd-54be0cb0cf7f.png)

## CODE(readv)
```c
#include <stdio.h>
#include <sys/uio.h>

#define BUF_SIZE 100

int main(int argc, char *argv[])
{
    struct iovec vec[2];

    char buf1[BUF_SIZE]={0,};
    char buf2[BUF_SIZE]={0,};
    int str_len;

    vec[0].iov_base = buf1;
    vec[0].iov_len = 5;
    vec[1].iov_base = buf2;
    vec[1].iov_len = BUF_SIZE;

    str_len = readv(0,vec,2);
    printf("Read bytes: %d\n",str_len);
    printf("First message: %s\n",buf1);
    printf("Second message: %s\n",buf2);    
}
```
## 출력
![Example3-result(1)](https://user-images.githubusercontent.com/79188587/167244355-fd88056a-d27c-461f-865a-df034de97109.PNG)
