#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 1024

int main(int argv, char* argc[]) {
  FILE* fp;
  char buf[MAX_BUF];
  int count;
  if (argv != 2) {
    fprintf(stderr, "usage : %s src\n", argc[0]);
    exit(1);
  }
  if (!(fp = fopen(argc[1], "rt"))) {
    perror("fopen");
    exit(1);
  }
  while (fgets(buf, MAX_BUF, fp)) {
    for (int idx = 0; buf[idx] != '\0'; idx++) {
      if (buf[idx] >= 'a' && buf[idx] <= 'z') buf[idx] += 'A' - 'a';
    }
    fprintf(stdout, "%s", buf);
  }

  return 0;
}
