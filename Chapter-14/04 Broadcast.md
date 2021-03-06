## 브로드캐스트(Broadcast)란?
> * 한번에 여러 호스트에게 데이터를 전송한다는 점에서 멀티캐스트와 유사하다.
> * 멀티캐스트는 그룹에 가입만 되어 있으면 데이터의 수신이 가능하다.
> * 브로드캐스트는 동일한 네트워크로 연결되어있는 호스트에게만 데이터 전송 대상이 제한된다.
> * 데이터 전송 시 사용되는 IP주소의 형태에 따라 두가지 형태로 나뉜다.

## Directed 브로드캐스트
> * IP주소를 네트워크 주소를 제외한 나머지 호스트 주소를 전부 1로 설정해서 얻을 수 있다.
> * 예를 들어 네트워크주소가 192.12.34인 네트워크에 연결되어있는 모든 호스트에게 데이터를 전송하려면 192.12.34.255로 전송하면된다.
> * 이렇듯 특정 지역의 네트워크에 연결된 모든 호스트에게 데이터를 전송하려면 이 방식을 사용하면 된다.

## Local 브로드캐스트
> * 로컬 브로드캐스트를 위해서는 255.255.255.255라는 IP주소가 특별히 예약되어 있다.
> * 예를 들어 네트워크 주소가 192.32.24인 네트워크에 연결되어 있는 호소트가 IP주소 255.255.255.255를 대상으로 데이터를 전송하면<br/>
> 192.32.24로 시작하는 IP주소의 모든 호스트에게 데이터를 전송한다.

## 브로드캐스트 사용법
> * 기본적으로 생성되는 소켓은 브로드캐스트 기반의 전송이 불가능하도록 설정되어 있다.
> * 그래서 몇가지 절차를 거칠 필요가 있다.(Sender에만 필요)
```c
int send_sock;
int bcast = 1; // SO_BROADCAST의 옵션정보를 1로 변경하기 위한 변수 초기화
send_sock = socket(PF_INET, SOCK_DGRAM, 0);
////////////////
setsockopt(send_sock, SOL_SOCKET, SO_BROADCAST, (void*)&bcast, sizeof(bcast));
///////////////
```
