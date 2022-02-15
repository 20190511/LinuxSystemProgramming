#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void SigUsrHandler(int signo) {
  if (signo == SIGUSR1) {
    printf("Received a SIGUSR1 signal\n");
  } else if (signo == SIGUSR2) {
    printf("Received a SIGUSR2 signal\n");
  } else {
    printf("Received unknown signal\n");
    printf("Terminate this process\n");
    exit(0);
  }
}
int main() {
  /* SIGUSR1 signal handler: SigUsrHandler */
  if (signal(SIGUSR1, SigUsrHandler) == SIG_ERR) {
    perror("signal");
    exit(1);
  }

  if (signal(SIGUSR2, SigUsrHandler) == SIG_ERR) {
    perror("signal");
    exit(1);
  }
  // USR1, USR2 interrupt 대기. kill -USR1 {PID}
  // linux에선 한번 signal 핸들러 생성시 여러번 호출될 수 있다.
  for (;;) pause();
}
