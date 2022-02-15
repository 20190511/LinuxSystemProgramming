#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
  if (argc == 2)  // ./square {int}
  {
    int argint = atoi(argv[1]);  // atoi를 이용하여 문자열을 int로.
    fprintf(stdout, "%d\n", argint * argint);  // 제곱값 출력.
  }
  return 0;
}
