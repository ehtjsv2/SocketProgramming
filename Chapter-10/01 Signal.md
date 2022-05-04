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

### sigaction으로 시그널 등록법
> struct sigaction act; // sigaction구조체 변수 선언
> act.sa_handler=read_childproc; // 시그널 발생되면 read_childproc함수 실행
> sigemptyset(&act.sa_mask); // sa_mask의 모든비트를 0으로 초기화
> act.sa_flags=0; // flags를 0으로 초기화
> sigaction(SIGCHILD, &act, 0); //SIGCHILD 시그널이 발생하면 act구조체변수에 저장된 함수를 실행

### 시그널과 Sleep()과의 관계
> 시그널이 발생되면 시그널에 해당하는 시그널 핸들러의 호출을 위해서 sleep함수의 호출로 블로킹 상태에 있던 프로세스는 깨어나게 된다.
> 교재의 예제를 보면 sleep(100)을햇지만 미리 실행했던 코드 alarm(2)의 2초가 지나자 시그널 핸들러의 함수호출을 위해 100초 되기전에 깨어나는 모습을 볼 수 있다.
