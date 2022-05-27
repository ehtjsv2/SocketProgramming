### 라이브러리
```c
#include <sys/epoll.h>
```

### 파일 디스크립터 저장소, 등록, 삭제, 변화대기 함수
* epoll 파일 디스크립터 저장소 생성
```
epoll_create
```
* 저장소에 파ㅣㄹ 디스크립터 등록 및 삭제
```
epoll_ctl
```
* select 함수와 마찬가지로 파일 디스크립터의 변화대기
```
epoll_wait
```
