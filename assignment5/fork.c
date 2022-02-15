#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int Var = 6;  // 전역 변수.
char Buf[] = "a write to stdout\n";

int main() {
  int var;  // 지역 변수. (main 함수의)
  pid_t pid;

  var = 88;  // 출력 확인용.
  write(STDOUT_FILENO, Buf,
        sizeof(Buf) - 1);  // write는 한번만 나온다. fork전이라서.
  printf("Before fork\n");

  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {
    // 자식 프로세스.
    Var++;
    var++;
  } else {
    // 부모 프로세스.
    sleep(2);  // 2초 기다림. -> 자식보다 늦게 출력됨.
  }

  printf("pid = %d, Var = %d, var = %d\n", getpid(), Var, var);
  // 자식 프로세스 Var = 7, var = 89
  // 부모 프로세스 Var = 6, var = 88
}
