#include <stdio.h>
#include <unistd.h>

#define MAX_BUF 256

int main(int argc, char *argv[]) {
  char buf[MAX_BUF];
  // get current working dir.
  // 에러면 null 포인터, 정상이면 buf에 복사.
  if (getcwd(buf, MAX_BUF) == NULL) {
    perror("getcwd");
    exit(1);
  }

  printf("%s\n", buf);
}
