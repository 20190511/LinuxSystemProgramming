#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF 128

int main() {
  int n, fd1[2], fd2[2];
  pid_t pid;
  char buf[MAX_BUF], parentBuf[MAX_BUF];

  if (pipe(fd1) == -1) {  // pipe 만들기 부모 <-> 자식
    perror("pipe");
    exit(1);
  }

  if (pipe(fd2) == -1) {  // pipe 만들기 부모 <-> 자식
    perror("pipe");
    exit(1);
  }

  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {  // 자식 프로세스
    close(fd1[1]);        // 자식의 파이프 출력을 막음
    close(fd2[0]);
    printf("Child : Wait for parent to send data\n");
    if ((n = read(fd1[0], buf, MAX_BUF)) == -1) {  // 파이프를 통해 데이터 읽음
      perror("read");
      exit(1);
    }
    printf("Child : Received data from parent : ");
    fflush(stdout);                // '\n' 이전에 출력
    write(STDOUT_FILENO, buf, n);  // stdout에 받은 데이터 씀. 출력.
    printf("Child : Send Data to Parent\n");
    strcpy(buf, "This is Child Data\n");
    write(fd2[1], buf, strlen(buf) + 1);
  } else {          // 부모 프로세스
    close(fd1[0]);  // 부모의 파이프로의 입력을 막음
    close(fd2[1]);
    strcpy(parentBuf, "This is Parent Data\n");  // 버퍼에 읽기
    printf("Parent: Send Data to Child\n");
    write(fd1[1], parentBuf, strlen(parentBuf) + 1);

    printf("Parent: Wait Data from Child\n");
    if ((n = read(fd2[0], parentBuf, MAX_BUF)) == -1) {
      perror("read");
      exit(1);
    }
    printf("Parent : Received Data from Child : ");
    fflush(stdout);
    write(STDOUT_FILENO, parentBuf, n);
  }
  exit(0);
}
