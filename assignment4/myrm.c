#include <stdio.h>

int main(int argc, char *argv[]) {
  int i;

  if (argc == 1) {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    exit(1);
  }

  for (i = 1; i < argc; i++) {  // 입력 받은 매개변수 만큼 지움.
    if (remove(argv[i])) {
      perror("remove");
      exit(1);
    }
  }
}
