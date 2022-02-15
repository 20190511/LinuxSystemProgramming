#include <stdio.h>

#define MAX_BUF 256

int main(int argc, char *argv[]) {
  FILE *src, *dst;
  char buf[MAX_BUF];

  if (argc != 3) {
    fprintf(stderr, "Usage: %s source destination\n", argv[0]);
    exit(1);
  }

  if ((src = fopen(argv[1], "rt")) == NULL) {
    perror("fopen");
    exit(1);
  }

  if ((dst = fopen(argv[2], "wt")) == NULL) {
    perror("fopen");
    exit(1);
  }

  while (fgets(buf, MAX_BUF, src)) {  // fgets는 한 줄씩.
    fputs(buf, dst);                  // EOF면 null 반환-> 반복문 탈출.
  }

  fclose(src);
  fclose(dst);
}
