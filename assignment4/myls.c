#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
  DIR *dp;
  struct dirent *dep;

  if ((dp = opendir(".")) == NULL) {
    perror("opendir");
    exit(0);
  }
  // dirent구조체와 DIR 포인터로 파일을 하나씩 읽음.
  while (dep = readdir(dp)) {
    printf("%s\n", dep->d_name);
  }
  // 다읽으면 dep == NULL.
  closedir(dp);
}
