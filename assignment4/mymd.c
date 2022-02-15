#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s dirname\n", argv[0]);
    exit(1);
  }

  /* 755 permission */  // rwxr-xr-x
  if (mkdir(argv[1], 0755)) {
    perror("mkdir");
    exit(1);
  }
}
