## 세마포어(Semaphore)란?
> * 뮤텍스와 유사하지만 여기서는 0과 1만을 사용하는 '바이너리 세마포어' 라는 것을ㄷ ㅐ상으로
> 쓰레드의 '실행순서 컨트롤' 중심의 동기화를 사용.
> * 아래에 사용하는 함수 네가지(semaphore.h 라이브러리사용)

```c
#include <semaphore.h>
int sem_init(sem_t *sem, int pshared, unsigned int value);
int sem_destroy(sem_t *sem);
```
> * sem -> 세마포어 생성/소멸 시  세마포어의 참조 값 저장을 위한 변수의 주소 값 전달,
> * pshared -> 0이외의 값 전달 시, 둘이상의 프로세스에 의해 접근 가능한 세마포어 생성, 0 전달시 하나의 프로세스 내에서만 접근 가능한 세마포어 생성, 우리는 하나의 프로세스 내에 존재하는 쓰레드의 동기화가 목적이므로 0을 전달
> * value -> 생성하는 세마포어의 초기 값 지정

```c
#include <semaphore.h>
int sem_post(sem_t * sem);
int sem_wait(sem_t * sem);
```

## 설명
> * sem_init 함수 호출 시 운영체제에 의해 세마포어 오브젝트 생성됨.
> * 이곳에는 세마포어 벨류 라 불리는 정수 하나 기록됨
> * 이 값은 sem_post 호출되면 1 증가하고 sem_wait 함수 호출되면 1감소한다. (단, 0보다 작아질 수는 없다)
> * 0상태에서 wait를 호출하면 블로킹에 빠진다, 단 다른곳에서 psot를 호출하면 블로킹을 탈출한다.(세마포어 초기밧은 1이라 가정)
> * 이것을 이용해서 동기화를 할 수있다
```c
swm_wait(&sem); // 여기는 지나가지만 다른곳의 wait는 블로킹에 빠트리게함
// 임계영역 시작
//
// 임계영역 끝
sem_post(&sem); // 다른곳의 wait 블로킹을 풀게하기위해.
```

## CODE
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void* read(void *arg);
void* accu(void *arg);
static sem_t sem_one;
static sem_t sem_two;
static int   num;

int main(int argc, char *argv[])
{
  pthread_t id_t1, id_t2;

  sem_init(&sem_one, 0, 0);
  sem_init(&sem_two, 0, 1);

  pthread_create(&id_t1, NULL, read, NULL);
  pthread_create(&id_t2, NULL, accu, NULL);

  pthread_join(id_t1, NULL);
  pthread_join(id_t2, NULL);

  sem_destroy(&sem_one);
  sem_destroy(&sem_two);
  return 0;
}

void* read(void *arg)
{
  int i;

  for (i = 0; i < 5; i++) {
    fputs("Input num: ", stdout);


    sem_wait(&sem_two);
    scanf("%d", &num);
    sem_post(&sem_one);
  }
  return NULL;
}

void* accu(void *arg)
{
  int sum = 0, i;

  for (i = 0; i < 5; i++) {
    sem_wait(&sem_one);
    sum += num;
    sem_post(&sem_two);
  }
  printf("Result: %d \n", sum);
  return NULL;
}
```
