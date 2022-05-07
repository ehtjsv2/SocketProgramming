## TTL이란?
> * 멀티캐스트 패킷의 전송을 위해서는 TTL이라는 것의 설정 과정을 반드시 거쳐야한다.
> * Time To Live 의 약자로 패킷을 얼마나 멀리 전달 할 것인가를 경정하는 주 요소가 된다.
> * 정수로 표현되며, 이 값은 라우터를 하나 거칠때마다 1씩 감소한다. 0이 되면 패킷은 더이상 전달되지 못한다.
> * 그렇다고 너무 크게 설정하면 네트워크 트래픽에 좋지 못한 영향을 끼친다.

## TTL 설정방법
> * Chpter9에서 설명한 소켓의 옵션설정으로 이루어진다.
> * 관련 프로토콜 레벨은 IPPROTO_IP이고 옵션이름은 IP_MULTICAST_TTL이다.

##### * 만약 TTL을 64로 설정한다면..
```c
int send_sock;
int time_live=64;
/////////////////
send_sock =socket(PF_INET, SOCK_DGRAM, 0);
setsockopt(send_sock, IPPROTO_TP, IP_MULTICAST_TTL, (void*)&time_live, sizeof(time_live));
/////////////////
```
## 멀티캐스트 그룹으로 가입 방법
> * 또한 소켓 옵션설정으로 이루어진다.
> * 관련 프로토콜 레벨은 IPPROTO_IP이고 옵션이름은 IP_ADD_MEMBERSHIP이다.

#### * 가입 예시
```c
int recv_sock;
struct ip_mreq join_adr;
/////////////////
recv_sock = socket(PF_INET, SOCK_DGRAM,0);
/////////////////
join_adr.imr_multiaddr.s_addr = "멀티캐스트 그룹의 주소정보";
jotin_adr.imr_ interface.s_addr= "그룹에 가입할 호스트의 주소정보";
```
