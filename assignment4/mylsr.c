#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_PATH 256

void JustDoIt(char *path) {
  DIR *dp;
  struct dirent *dep;
  struct stat statbuf;
  char fullpath[MAX_PATH];

  if ((dp = opendir(path)) == NULL) {  // open path.
    perror("opendir");
    exit(0);
  }

  printf("\n%s:\n", path);
  while (dep = readdir(dp)) {
    if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)
      continue;
    printf("%s\n", dep->d_name);
  }

  // rewind를 이용해 디렉토리안도 재귀적으로 읽기.
  rewinddir(dp);
  while (dep = readdir(dp)) {
    if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)
      continue;
    strcpy(fullpath, path);
    strcat(fullpath, "/");
    strcat(fullpath, dep->d_name);  // path/(filename)
    if (lstat(fullpath, &statbuf)) {
      perror("lstat");
      exit(1);
    }
    if (S_ISDIR(statbuf.st_mode)) {  // 디렉토리라면
      JustDoIt(fullpath);  // 재귀호출 -> 디렉토리안도 가능.
    }
  }

  closedir(dp);
}

int main() {
  JustDoIt(".");  // 현재 디렉토리 열기.
}
