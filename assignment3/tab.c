#include <stdio.h>

// 참 거짓 열거체로 지정.
enum { FALSE, TRUE };

void conv(char *fname)  // 변경할 파일명을 파라미터로.
{
  FILE *src, *dst;  // 파일 포인터
  char fdest[40];
  int ch, first;

  if ((src = fopen(fname, "rt")) == NULL) {
    perror("fopen");
    return;
  }  // 소스 파일 읽기 모드로 열기.

  strcpy(fdest, fname);
  strcat(fdest, ".t");
  if ((dst = fopen(fdest, "wt")) == NULL) {
    perror("fopen");
    return;
  }  // fname.t 이름으로 쓰기 모드.

  first = TRUE;
  while ((ch = fgetc(src)) != EOF) {  // EOF까지 src에서 한글자 읽기.
    if (first && ch == '\t') {  // 맨 처음의 탭을 스페이스 네 개로 변환.
      fputc(' ', dst);
      fputc(' ', dst);
      fputc(' ', dst);
      fputc(' ', dst);
    } else {
      fputc(ch, dst);
      if (first) first = FALSE;
      if (ch == '\n')  // 줄바꾸면 처음이므로 바꾸기.
        first = TRUE;
    }
  }

  fclose(src);
  fclose(dst);
}

int main(int argc, char *argv[]) {
  while (--argc) {
    conv(argv[argc]);
  }
}
