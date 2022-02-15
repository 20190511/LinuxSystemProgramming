#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc == 3) {
    char fc = argv[2][0];
    char* wanted_file = argv[1];

    FILE* fp;
    if (!(fp = fopen(wanted_file, "r"))) {
      perror("fopen");
      exit(1);
    }
    int cnt = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
      if (ch == fc) cnt++;
    }
    printf("%d\n", cnt);
  }
}
