#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF 128

int main() {
  int n, fd[2];
  pid_t pid;
  char buf[MAX_BUF];

  if (pipe(fd) == -1) {  // pipe 만들기 부모 <-> 자식
    perror("pipe");
    exit(1);
  }

  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {  // 자식 프로세스
    close(fd[1]);         // 자식의 파이프 출력을 막음
    printf("Child : Wait for parent to send data\n");
    if ((n = read(fd[0], buf, MAX_BUF)) == -1) {  // 파이프를 통해 데이터 읽음
      perror("read");
      exit(1);
    }
    printf("Child : Received data from parent: ");
    fflush(stdout);                // '\n' 이전에 출력
    write(STDOUT_FILENO, buf, n);  // stdout에 받은 데이터 씀. 출력.
  } else {                         // 부모 프로세스
    close(fd[0]);                  // 부모의 파이프로의 입력을 막음
    strcpy(buf, "Hello, World!\n");  // 버퍼에 읽기
    printf("Parent: Send data to child\n");
    write(fd[1], buf, strlen(buf) + 1);
  }
  exit(0);
}
