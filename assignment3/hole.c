#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  int fd;
  char ch = '\0';
  // 파일 생성. 0400 이므로 r--------
  if ((fd = creat("file.hole", 0400)) < 0) {
    perror("creat");
    exit(1);
  }
  // 1023번 인덱스로 파일 포인터 이동.
  if (lseek(fd, 1023, SEEK_SET) < 0) {
    perror("lseek");
    exit(1);
  }
  // 널문자를 1024번째에 넣어서 1024바이트의 파일 생성.
  write(fd, &ch, 1);

  close(fd);
}
