#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  if (argc == 2) {
    char* cmd_vec[] = {"wc", "-w", argv[1], NULL};

    int pid;
    if ((pid = fork()) < 0) {
      perror("fork");
      exit(1);
    } else if (pid == 0) {
      execvp(cmd_vec[0], cmd_vec);
    } else {
      wait(NULL);
      return 0;
    }
  }
}
