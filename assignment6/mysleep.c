#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void SigAlarmHandler(int signo) {
  /* nothing to do, just return to wake up the pause */
  return;
}

unsigned int mysleep(unsigned int nsecs) {
  /* SIGALRM signal handler: SigAlarmHandler */
  if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR) {
    return nsecs;  // 에러시 반환값.
  }
  alarm(nsecs);  // nsecs후에 알림. -> SIGALRM signal.
  // -> 핸들러 호출.

  pause();

  return alarm(0);  // 남은 시간 반환 -> 정확히 nsecs만큼 기다렸는가?
}

int main() {
  printf("Wait for 5 seconds...\n");

  mysleep(5);
}
