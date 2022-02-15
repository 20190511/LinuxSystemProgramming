#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
  int pid;

  if ((pid = fork()) < 0) {  // fork로 자식 프로세스 생성.
    perror("fork");
    exit(1);  // pid == -1이면 fork에서 에러.
  }
  // 이하 코드부터 부모와 자식으로 나뉘게 됨.
  else if (pid == 0) {  // pid가 0이면 자식 프로세스
    printf("I am %d. My parent is %d.\n", getpid(), getppid());
  } else {
    // pid가 0이 아니면 부모프로세스
    printf("I am %d. My child is %d.\n", getpid(), pid);
  }
}
