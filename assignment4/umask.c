#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
  umask(0);  // 파일 권한 기본값을 0으로. rwx 다 허용.
  if (creat("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) <
      0) {  // bar라는 파일이
    //	rw-rw-rw-로 생성.
    perror("creat");
    exit(1);
  }
  umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  // ---rw-rw-를 제거하게 됨.
  /* Set file mode creation mask: S_IRGRP, S_IWGRP, S_IROTH, S_IWOTH */
  if (creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) <
      0) {  // rw-------
    perror("creat");
    exit(1);
  }
}
