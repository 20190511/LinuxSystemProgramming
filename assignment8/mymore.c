#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int fd[2];  // pipe용 File Descriptor
  pid_t child;

  if (pipe(fd) == -1) {
    perror("pipe");
    exit(1);
  }

  child = fork();
  if (child == (pid_t)(-1)) {  // ERR
    perror("fork");
    exit(1);
  } else if (child == (pid_t)0) {  // Child
    close(1);                      // stdout close
    close(fd[0]);                  // pipe-in close

    if (dup(fd[1]) == -1) {  // 자리가 빈 가장 낮은 번호의 fd로 변경
      perror("dup");
      exit(1);
    }
    // fd[1] => 1 STDOUT
    if ((execlp("ls", "ls", "-l", NULL)) == -1) {  // exec list + PATH
      perror("execlp");
      exit(1);
    }
    // ls -l의 출력이 pipe를 통해 부모의 fd[0]의 입력으로 주어짐
    // child -> parent
  } else {         // parent
    close(0);      // stdin close
    close(fd[1]);  // pipe-out close

    if (dup2(fd[0], 0) == -1) {  // stdin으로 변경
      perror("dup");
      exit(1);
    }
    // pipe로 부터
    if ((execlp("more", "more", NULL)) == -1) {  // more 실행
      perror("execlp");
      exit(1);
    }
  }

  return 0;
}
