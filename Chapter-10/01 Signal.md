### 시그널이란?
> 특정 상황이 됐을 때 운영체제가 프로세스에게 해당 상황이 발생했음을 알리는 메세지를 뜻한다.<br/>
> SIGALAM -> alarm함수호출을 통해 등록된 시간이 된 상황
> SIGINT -> ctrl + c 가 입력된 상황
> SIGCHILD -> 자식 프로세스가 종료된 상황

### 시그널 등록이란?
> 특정 상황에서 프로세스가 운영체제로부터 시그널을 받기위해서는 해당상황에 대한 등록과정을 거쳐야한다.<br/>

#### 시그널 함수로 시그널 등록법
> signal(SIGCHILD, mychild)
> ㄴ자식 프로세스가 종료되면 mychild라는 함수를 호출해달라
> siganl(SIGALAM, timeout);
> ㄴalarm함수호출통해 등록된 시간이 지나면 timeout함수 호출해달라.
> signal(SIGINT, keycontrol)
> ㄴCTRL + C가 입력되면 keycontrol 함수를 호출해달라.

