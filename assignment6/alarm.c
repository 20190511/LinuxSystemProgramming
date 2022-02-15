#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static unsigned int AlarmSecs;  // 주기.

void SigAlarmHandler(int signo) {
  if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR) {
    perror("signal");
    exit(1);
  }  // nsecs마다 핸들러 설정.

  alarm(AlarmSecs);
  printf(".");
  fflush(stdout);  // '\n'까지 안기다리고 출력하게 됨.

  return;
}

int SetPeriodicAlarm(unsigned int nsecs) {
  if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR) {
    return -1;
  }

  AlarmSecs = nsecs;  // 주기 설정.

  alarm(nsecs);  // nsecs후 SIGALRM signal.

  return 0;
}
int main() {
  printf("Doing something every one seconds\n");

  SetPeriodicAlarm(1);  // 1초마다 점 출력.

  for (;;) pause();
}
