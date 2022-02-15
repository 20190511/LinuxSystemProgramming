#include <stdio.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]) {
  FILE *src, *dst;
  char buf[MAX_BUF];
  int count;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s source destination\n", argv[0]);
    exit(1);
  }

  if ((src = fopen(argv[1], "rb")) == NULL) {
    perror("fopen");
    exit(1);
  }

  if ((dst = fopen(argv[2], "wb")) == NULL) {
    perror("fopen");
    exit(1);
  }

  while (count = fread(buf, 1, MAX_BUF, src)) {
    fwrite(buf, 1, count, dst);  // fread는 바이너리를 읽는 함수.
    // src에서 count만큼 꺼내서 dst에 전달.
    // 배열의 원소의 크기는 MAX_BUF이고 1만큼 읽는다.
  }

  fclose(src);
  fclose(dst);
}
