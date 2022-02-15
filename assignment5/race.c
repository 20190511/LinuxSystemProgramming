#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void CharAtaTime(char *str)  // 문자열을 문자 하나씩 출력하는 함수
{
  char *ptr;
  int c, i;

  setbuf(stdout, NULL);  // 버퍼 없이 출력하게 됨.
  for (ptr = str; c = *ptr++;) {
    for (i = 0; i < 999999; i++)  // 컨텍스트 스위칭 유발하게 됨.
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
    CharAtaTime("output from parent\n");
  }  // race condition을 만족하여 겹쳐 출력됨.
}
