#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CMD 256

void DoCmd(char *cmd) {
  printf("Doing %s", cmd);
  sleep(1);
  printf("Done\n");

  pthread_exit(NULL);  // 터미널 종료.
}
int main() {
  char cmd[MAX_CMD];
  pthread_t tid;

  while (1) {
    printf("CMD> ");
    fgets(cmd, MAX_CMD, stdin);
    if (cmd[0] == 'q') break;

    if (pthread_create(&tid, NULL, (void *)DoCmd, (void *)cmd) < 0) {
      perror("pthread_create");
      exit(1);
    }  // start routine이 DoCmd이고 파라미터가 cmd인 쓰레드 생성

#if 1  // 쓰레드가 종료될때까지 기다림. -> 동시에 여러 커맨드 불가.
    pthread_join(tid, NULL);
#endif
  }
}
