#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void sigHandler(int signo) {
  printf("After Child terminated\n");
  exit(0);
}

int main() {
  int pid;
  signal(SIGCHLD, sigHandler);  // child process가 끝나면 핸들러 호출.
  printf("Before fork\n");
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {
    printf("Child pid : %d\n", getpid());
  } else {
    printf("Parent pid : %d\n", getpid());
    while (1)
      ;  // 무한 루프중 child process가 종료됨.
         // 핸들러에 의해 종료됨. -> asynchronous.
  }
}
