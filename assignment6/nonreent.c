#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void MyAlarmHandler(int signo) {
  struct passwd *rootptr;

  signal(SIGALRM, MyAlarmHandler);  // 1초마다 반복하게 됨
  alarm(1);

  printf("in signal handler\n");

  if ((rootptr = getpwnam("root")) ==
      NULL) {  // for문 도중 lsp51이 아닌 root의 정보를 읽어 corrupted.
    perror("getpwnam");  // getpwnam이 nonreent함수이기 때문에 동시에 실행하면
                         // 예상외의 결과가 나옴.
    exit(1);
  }

  return;
}
int main() {
  struct passwd *ptr;

  signal(SIGALRM, MyAlarmHandler);  // 핸들러 설정.
  alarm(1);                         // 1초뒤 알람.

  for (;;) {
    if ((ptr = getpwnam("lsp51")) == NULL) {  // ptr이 lsp51의 정보를 가리킴.
      perror("getpwnam");
      exit(1);
    }

    if (strcmp(ptr->pw_name, "lsp51") != 0) {
      printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
      exit(0);
    }
  }
}
