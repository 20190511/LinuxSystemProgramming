#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  DIR* dirp;
  struct dirent* dirn;
  int timed_ = 0;
  time_t mostrecent;           // 가장 최근 생성된 시각.
  char* mostrecentfilename;    // 해당 파일 이름.
  if (!(dirp = opendir(".")))  // 현재 디렉토리 탐색.
  {
    perror("opendir");
    exit(1);
  }
  while (dirn = readdir(dirp))  // dirn이 NULL이면 다 읽은것.
  {
    struct stat filestat;
    stat(dirn->d_name, &filestat);  // stat으로 파일 정보 확인.
    if (!timed_)  // 맨 처음 파일이면 mostrecent에 대입.
    {
      timed_ = 1;
      mostrecent = filestat.st_mtime;
      mostrecentfilename = dirn->d_name;
    } else {
      if (mostrecent < filestat.st_mtime)  // 비교후 대입.
      {
        mostrecent = filestat.st_mtime;
        mostrecentfilename = dirn->d_name;
      }
    }
    //	printf("%s\n", dirn->d_name);
  }
  printf("%s\n", mostrecentfilename);  // 이름 출력.
  return 0;
}
