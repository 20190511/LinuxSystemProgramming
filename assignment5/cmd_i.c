#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CMD 256

void DoCmd(char *cmd)  // 1초만 기다리는 건데
{                      // 연속으로 치면 따로 실행됨.
  printf("Doing %s", cmd);
  sleep(1);
  printf("Done\n");
}

int main() {
  char cmd[MAX_CMD];  // 커맨드 입력 버퍼

  while (1) {
    printf("CMD> ");
    fgets(cmd, MAX_CMD, stdin);
    if (cmd[0] == 'q')  // q이면 입력 종료.
      break;

    DoCmd(cmd);
  }
}
