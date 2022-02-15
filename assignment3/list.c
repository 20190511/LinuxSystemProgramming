#include <stdio.h>

#define MAX_BUF 256

int main(int argc, char *argv[]) {
  FILE *fp;  // 파일 포인터
  char buf[MAX_BUF];
  int line;

  if (argc != 2) {  // list src 식으로 안하면.
    printf("Usage: %s filename\n", argv[0]);
    exit(1);
  }

  if ((fp = fopen(argv[1], "rt")) == NULL) {
    perror("fopen");
    exit(1);
  }

  line = 1;
  while (fgets(buf, MAX_BUF, fp)) {
    // fgets는 다 읽으면 0 반환.
    // 한줄을 버퍼만큼 읽어서 출력. \n을 구별하여 출력하게 됨.
    printf("%4d: %s", line++, buf);
  }

  fclose(fp);
}
