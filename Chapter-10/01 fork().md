# fork()란??
> 부모 프로세스에서 자식 프로세스를 하나 복제 생성해 주는 역할을 한다.
> 이때 복제 생성 시, 부모 프로세스와 같은 프로세스가 만들어진다.
> fork()함수의 리턴값은 부모프로세스에서는 자식프로세스의 PID(Process ID)가 들어가고
> 자식프로세스에는 pork의 리턴값은 0이 들어간다.

# 코드
> ![image](https://user-images.githubusercontent.com/79188587/165890961-e320e9e2-ddf4-4a18-ae5b-4657cfe88c92.png)

# 실행결과
> ![image](https://user-images.githubusercontent.com/79188587/165890916-71d4caee-208e-4a20-b212-119e924509f2.png)

> 결과를 보면 child process가 출력한 문장의 위치가 프로세스가 끝난후 출력 된것을 볼 수 있다.
> 이결과로보아 부모프로세스의 코드실행이 우선이라는 것을 알 수 있다.
