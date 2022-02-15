#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s dirname\n", argv[0]);
    exit(1);
  }
  // chdir -> cd. pwd바꾸기.
  // 이 메인함수의 pwd는 파라미터대로.
  // 종료뒤 유저의 pwd는 그대로.
  if (chdir(argv[1]) < 0) {
    perror("chdir");
    exit(1);
  }
}
