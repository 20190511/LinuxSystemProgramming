#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s dirname\n", argv[0]);
    exit(1);
  }
  // argv[1]의 파일 디렉토리를 지움. 에러면 0.
  if (rmdir(argv[1])) {
    perror("rmdir");
    exit(1);
  }
}
