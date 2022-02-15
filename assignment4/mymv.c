#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s old new\n", argv[0]);
    exit(1);
  }

  if (rename(argv[1], argv[2])) {
    // argv[1] => argv[2] rename.
    perror("rename");
    exit(1);
  }
}
