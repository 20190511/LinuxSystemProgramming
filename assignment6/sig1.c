#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void SigIntHandler(int signo) {
  printf("Received a SIGINT signal\n");
  printf("Terminate this process\n");

  exit(0);
}

int main() {
  /* SIGINT signal handler: SigIntHandler */
  /* signal */
  signal(SIGINT, SigIntHandler);
  // interrupt signal시 지정한 핸들러 호출.
  printf("Press ^C to quit\n");

  for (;;)  // interrupt signal 대기.
    pause();
}
