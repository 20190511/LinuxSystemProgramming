#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid;
  char *argv[] = {"mycp", "exec.c", "exec2.c", NULL};
  // 미리 지정한 명령어. 마지막은 NULL.
  // execl - list로 exec.
  if ((pid = fork()) < 0) {  // 자식 프로세스가 명령 수행.
    perror("fork");
    exit(1);
  } else if (pid == 0) {
    // mycp exec.c exec2.c
    if (execl("/home/lsp51/assignment3/mycp", "mycp", "exec.c", "exec2.c",
              NULL)) {
      perror("execl");
      exit(1);
    }
  }
  if (waitpid(pid, NULL, 0) < 0) {  // 자식프로세스가 끝날때 까지 기다림.
    perror("waitpid");
    exit(1);
  }

  // execv - vector로 exec.
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {
    // mycp exec.c exec2.c
    if (execv("/home/lsp51/assignment3/mycp", argv)) {
      perror("execv");
      exit(1);
    }
  }
  if (waitpid(pid, NULL, 0) < 0) {
    perror("waitpid");
    exit(1);
  }

  // execlp -> envp포함 exec.
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {
    // execute 'env' from PATH
    if (execlp("env", "env", NULL)) {
      perror("execlp");
      exit(1);
    }
  }
  if (waitpid(pid, NULL, 0) < 0) {
    perror("waitpid");
    exit(1);
  }
}
