#include <stdio.h>
#include <stdlib.h>

#include "synclib.h"
#define NLOOPS 5  // 5번 루프

int main() {
  int i;
  pid_t pid;

  TELL_WAIT();  // pipe를 이용한 동기화
  // pipe 생성
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid > 0) {
    for (i = 0; i < NLOOPS; i++) {
      TELL_CHILD();
      printf("Parent: Tell to child\n");
      printf("Parent: Wait for child to tell\n");
      WAIT_CHILD();  // TELL_PARENT가 호출될 때까지 기다림
    }
  } else {
    for (i = 0; i < NLOOPS; i++) {
      printf("Child: Wait for parent to tell\n");
      WAIT_PARENT();  // TELL_CHILD가 호출될 때까지 기다림 : 동기화
      TELL_PARENT();
      printf("Child: Tell to parent\n");
    }
  }
}
