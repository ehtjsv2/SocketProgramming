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

#select()
> * int select(int maxfd, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timaval *timeout)
>   * maxfd - 검사 대상이 되는 파일 디스크립터의 수
>   * readset - 수신 데이터의 존재여부에 관심있는 파일 디스크립터
>   * writeset - 데이터의 전송 가능여부 에 관심있는 파일 디스크립터
>   * exceptset - 예외상황 발생여부에 관심있는 파일 디스크립터
>   * timeout - select함수가 무한정 블로킹에 빠지지않도록 타임아웃을 설정
>   * 반환값 - 오류는 -1, 타임아웃 시에는 0, 변화발생시 변화 발생한 파일디스크립터의 개수
