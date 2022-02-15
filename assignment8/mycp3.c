#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fdin, fdout;
  char *src, *dst;
  struct stat statbuf;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s source destination\n", argv[0]);
    exit(1);
  }

  if ((fdin = open(argv[1], O_RDONLY)) < 0) {
    perror("open");
    exit(1);
  }
  if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0) {
    perror("open");  // 복사 파일 생성
    exit(1);
  }

  if (fstat(fdin, &statbuf) < 0) {  // 파일 정보 가져오기
    perror("fstat");
    exit(1);
  }
  if (lseek(fdout, statbuf.st_size - 1, SEEK_SET) <
      0) {  // 특정 사이즈를 만들기.
    perror("lseek");
    exit(1);
  }
  write(fdout, "", 1);  // 마지막에 쓰기를 통해 파일을 원하는 사이즈로 만들기.

  if ((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) ==
      (caddr_t)-1) {  // read
    perror("mmap");   // fdin으로 읽어 메모리 공간에 매핑.
    exit(1);
  }
  if ((dst = mmap(0, statbuf.st_size, PROT_WRITE, MAP_SHARED, fdout, 0)) ==
      (caddr_t)-1) {  // write
    perror("mmap");   // fdout을 읽어서 메모리 공간에 매핑
    exit(1);
  }

  memcpy(dst, src, statbuf.st_size);  // 복사

  close(fdin);
  close(fdout);
}
