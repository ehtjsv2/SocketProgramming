## writev 와 readv 란??
> * 데이터의 송수신 효율성을 향상시키위해 사용
> * 데이터를 모아서 전송, 모아서 수신 기능의 함수이다.

## writev
> * ssize_t writev(int filedes, const struct iovec * iov, int iovcnt);
>   * filedes - 파일 디스크립터
>   * iov - 구조체 iovec 배열 주소 값 전달
>   * iovcnt - iov의 배열의 길이정보 전달

## struct iovec
```c
struct iovec
{
  void *iov_base; // 버퍼의 주소정보
  size_t iov_len; // 버퍼의 크기정보
}
```

## CODE
```c

```
