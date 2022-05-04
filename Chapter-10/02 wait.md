## Wait()를 왜 해야하는가?
> 좀비프로세스로 남아있는 자식프로세스의 확실한 소멸을 위해.

## wait()
> pid_t wait(int * statloc)
> 위 함수가 호출되었을 때, 이미 종료된 자식 프로세스가 있다면, 자식프로세스가 종료되면서 전달한 값(exit값 or return값)이 매개변수로 전달된
> 주소의 변수에 저장된다.<br/>
> 이 변수에 저장되는 값에는 전달한 값 이외에도 다른정보가 있으니 밑의 매크로 함수를 통해서 값의 분리과정을 거쳐야 한다.

## WIFEXITED() 와 WEXITSTATUS()
> WIFEXITED()는 자식 프로세스가 정상 종료한 경우 참을 반환 // Wait IF EXITED 가 아닌가 추론..<br/>
> WEXISTATUS()는 자식프로세의 전달값을 반환 // Wait EXIT STATUS가 아닌가 추론,,<br/>

### 사용법
'''cpp
  int status;
  wait(&status);
  if(WIFEXITED(status)){  // 정상종료되었는가>?
    puts("Nomal termination!");
    printf("Child pass num: %d", WEXITSTATUS(status));  // 그렇다면 반환 값은?
  }
'''
end<br/>
