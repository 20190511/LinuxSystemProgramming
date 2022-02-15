#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]) {
  int fd1, fd2, count;
  char buf[MAX_BUF];  // buffer.

  if (argc != 3) {  // mycp src dst 식으로 들어와야 함을 의미.
    printf("Usage: %s source destination\n", argv[0]);
    exit(1);
  }

  if ((fd1 = open(argv[1], O_RDONLY)) < 0) {
    perror("open");  // 열기에 실패할때.
    exit(1);
  }

  if ((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
    perror("open");  // 파일을 만들어서 쓰기 모드로 열기.
    exit(1);         // 0644는 팔진법. rwx 지정.
                     // O_TRUNC는 파일의 모든 내용을 지우고 시작.
  }
  // read는 버퍼의 크기만큼 버퍼에 복사하고 읽은 크기 만큼 반환.
  // 파일의 끝이면 0 반환 -> 반복문 탈출.
  while (count = read(fd1, buf, MAX_BUF)) {
    write(fd2, buf, count);  // 버퍼에 있는 만큼 복사.
  }

  close(fd1);
  close(fd2);
}
