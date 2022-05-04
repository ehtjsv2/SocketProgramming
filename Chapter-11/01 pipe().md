## 파이프를 왜 써야하는가?
> ● 프로세스간 통신을 위해(부모 프로세스, 자식프로세스간)

## 파이프 통신간 주의사항
> ● 파이프를 두개 선언해서 fds1[0]은 부모read용 fds2[1]은 부모write용, fds1[1]은 자식 write용, fds2[0]은 자식read용 이렇게사용해라.

## 예시
```c
#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc, char*argv[]){
    int fds1[2], fds2[2];
    char str1[] = "Who are you?";
    char str2[] = "Thank you for your message";
    char buf[BUF_SIZE];
    pid_t pid;
    pipe(fds1), pipe(fds2);
    pid = fork();
    if(pid == 0){
        write(fds1[1],str1,sizeof(str1));
        read(fds2[0],buf,BUF_SIZE);
        printf("Child proc output: %s\n",buf);
    }

    else{
        read(fds1[0],buf,BUF_SIZE);
        printf("Parent proc output : %s\n",buf);
        write(fds2[1],str2, sizeof(str2));
        sleep(3);
    }

    return 0;
}
```
## result
```
Parent proc output : Who are you?
Child proc output: Thank you for your message

```
