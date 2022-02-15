#include <stdio.h>
#include <stdlib.h>

void myexit1() { printf("first exit handler\n"); }

void myexit2() { printf("second exit handler\n"); }
int main() {
  /* Add myexit2 to exit functions */
  if (atexit(myexit2) != 0) {  // exit을 하면서 다음 handler 제공.
    perror("atexit");
    exit(1);
  }

  if (atexit(myexit1) != 0) {
    perror("atexit");
    exit(1);
  }

  if (atexit(myexit1) != 0) {
    perror("atexit");
    exit(1);
  }

  printf("main is done\n");
  // main이 끝나고 exit할때는 스택으로 1 1 2순으로 출력/실행됨.
}
