#include <stdio.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]) {
  FILE *src1, *src2, *dst;
  char buf[MAX_BUF];
  int count;

  if (argc != 4) {
    fprintf(stderr, "Usage: %s source1 source2 dest\n", argv[0]);
    exit(1);
  }

  if ((src1 = fopen(argv[1], "rb")) == NULL) {
    perror("fopen");
    exit(1);
  }
  if ((src2 = fopen(argv[2], "rb")) == NULL) {
    perror("fopen");
    exit(1);
  }
  if ((dst = fopen(argv[3], "wb")) == NULL) {
    perror("fopen");
    exit(1);
  }
  // src1과 src2의 데이터를 읽어 dst에 복사.
  while (count = fread(buf, 1, MAX_BUF, src1)) {
    fwrite(buf, 1, count, dst);
  }

  while (count = fread(buf, 1, MAX_BUF, src2)) {
    fwrite(buf, 1, count, dst);
  }

  fclose(src1);
  fclose(src2);
  fclose(dst);
}
