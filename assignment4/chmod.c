#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
  struct stat statbuf;

  if (stat("bar", &statbuf) < 0) {  // bar의 파일 정보 입력 받기.
    perror("stat");
    exit(1);
  }
  // change permission
  // bar의 rwx에 그룹 write를 삭제 후 실행이 가능한 유저 아이디 입력.
  if (chmod("bar", (statbuf.st_mode & ~S_IWGRP) | S_ISUID) < 0) {
    perror("chmod");
    exit(1);
  }

  /* S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH : ON */
  // rw-r--r-- | USER GROUP OTHER
  if (chmod("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0) {
    perror("chmod");
    exit(1);
  }
}
