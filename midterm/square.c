#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
  if (argc == 2) {
    int argint = atoi(argv[1]);
    fprintf(stdout, "%d\n", argint * argint);
  }
  return 0;
}
