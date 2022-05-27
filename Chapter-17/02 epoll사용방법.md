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

### epoll_create
```c
int epoll_create(int size);
```
* int epfd를 미리 선언해서 epfd에 반환해주길 바람.
* size는 저장소의 크기

### epoll_ctl
```c
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```
* epfd-> 관찰대상 들록할 epoll 저장소
* op -> 관찰대상의 추가, 삭제 또는 변경여부 지정 (EPOLL_CTL_ADD , EPOLL_CTL_DEL)
* fd -> 등록할 관찰대상의 파일디스크립터
* event -> 관찰대상의 이벤트 유형(보통 ctl하기전에 event설정 먼저해야한다.)

### event
```c
struct epoll_event event;
---
event.events=EPOLLIN; // 수신할 데이터가 존재하는 상황
event.data.fd = sockfd;
epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
---
```
* 현재 배우는 과정에서는 EPOLLIN 이외에 EPOLLET 또는 EPOLLONESHOT 정도 사용한다.

### epoll_wait
```c
int epoll_wait(int epfd, struct epoll_evnet * events, int amxevents, int timeout);
```
* epfd -> epoll저장소
* events -> 변화가 생긴 디스크립터가 채워질 배열
* maxevents -> 두번째 인자에 등록가능한 최대 이벤트 수
* timeout -> 1/1000초 단위의 대기시간, -1 전달 시 blocking
```c
int event_cnt;
struct epoll_event *ep_events;
---
ep_events=malloc(sizeof(struct epoll_event)*EPOLL_SIZE); // 
---
event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
```

### CODE
```c

```
