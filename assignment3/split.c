#include <stdio.h>
#include <unistd.h>

#define MAX_BUF 1024

long filesize(FILE *fp) {
  long cur, size;

  cur = ftell(fp);          // fp의 현재 가리키고 있는 포인터.
  fseek(fp, 0L, SEEK_END);  // fp의 마지막 요소로 포인터를 가리킴.
  size = ftell(fp);  // ftell은 시작부터 현재까지로 -> 처음부터 끝이므로
  // size가 파일 크기가 됨.
  fseek(fp, cur, SEEK_SET);  // 이전에 가리키고 있던 곳으로 설정.
  return (size);
}

int main(int argc, char *argv[]) {
  FILE *src, *dst1, *dst2;
  char buf[MAX_BUF];
  int count, size;

  if (argc != 4) {  // src를 두개로 나눔.
    fprintf(stderr, "Usage: %s source dest1 dest2\n", argv[0]);
    exit(1);
  }

  if ((src = fopen(argv[1], "rb")) == NULL) {
    perror("fopen");
    exit(1);
  }
  if ((dst1 = fopen(argv[2], "wb")) == NULL) {
    perror("fopen");
    exit(1);
  }
  if ((dst2 = fopen(argv[3], "wb")) == NULL) {
    perror("fopen");
    exit(1);
  }

  size = filesize(src) / 2;  // 반으로 나누기 위한.

  while (size > 0) {                            // 처음 절반.
    count = (size > MAX_BUF) ? MAX_BUF : size;  // size만큼 읽기 위해.
    fread(buf, 1, count, src);
    fwrite(buf, 1, count, dst1);
    size -= count;
  }

  while ((count = fread(buf, 1, MAX_BUF, src)) > 0) {
    // 남은 절반
    fwrite(buf, 1, count, dst2);
  }

  fclose(src);
  fclose(dst1);
  fclose(dst2);
}
