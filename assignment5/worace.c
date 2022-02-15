#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void CharAtaTime(char *str) {
  char *ptr;
  int c, i;

  setbuf(stdout, NULL);  // stdout에 버퍼를 주지 않음>> 바로 출력.
  for (ptr = str; c = *ptr++;) {
    for (i = 0; i < 999999; i++)  // context switch유도.
      ;
    putc(c, stdout);
  }
}
int main() {
  pid_t pid;

  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {
    CharAtaTime("output from child\n");
  } else {
    wait(NULL);                           // 자식프로세스를 기다림.
    CharAtaTime("output from parent\n");  // 따라서 자식의 함수가 다 출력되고
                                          // 부모의 함수가 출력됨.
  }
}
