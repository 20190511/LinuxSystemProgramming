#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc == 3)  // ./count {file} {char}.
  {
    char fc = argv[2][0];         // 찾을 문자.
    char* wanted_file = argv[1];  // 검색 파일.

    FILE* fp;
    if (!(fp = fopen(wanted_file, "r")))  // 읽기 모드로 open.
    {
      perror("fopen");
      exit(1);
    }
    int cnt = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF)  // fgetc로 한글자씩.
    {
      if (ch == fc)  // 같은 문자라면 cnt++.
        cnt++;
    }
    printf("%d\n", cnt);
  }
}
