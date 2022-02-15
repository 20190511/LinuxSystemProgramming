#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
  pid_t pid;
  int status;

  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {
    printf("I'm a child\n");
    sleep(2);
  } else {
    wait(&status);  // wait안에는 기다린 프로세스의 종료상태.
    printf("A child killed with %d status\n", status);
    // 0 이면 정상. 아니면 에러.
  }
}
