#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *src, *dst;
  int ch;

  if (argc != 3) {  // tcp1 src dst 으로 사용해야 함.
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

  while ((ch = fgetc(src)) != EOF) {  // fgetc, fputc는 한 캐릭터씩 읽음.
    fputc(ch, dst);  // null 까지 dst에 작성. EOF만나면 종료.
  }

  fclose(src);
  fclose(dst);
}
