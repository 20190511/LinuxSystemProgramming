#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  if (argc == 2)  // ./mywc {file}
  {
    char* cmd_vec[] = {"wc", "-w", argv[1], NULL};
    // vector로 저장.
    int pid;
    if ((pid = fork()) < 0) {
      perror("fork");
      exit(1);
    } else if (pid == 0) {  // 자식프로세스에서 execvp. PATH에서 wc를 찾아 exec.
      execvp(cmd_vec[0], cmd_vec);
    } else {
      // 자식 프로세스가 끝날때 까지 기다림.
      wait(NULL);
      return 0;
    }
  }
}
