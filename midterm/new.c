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
  time_t mostrecent;
  char* mostrecentfilename;
  if (!(dirp = opendir("."))) {
    perror("opendir");
    exit(1);
  }
  while (dirn = readdir(dirp)) {
    struct stat filestat;
    stat(dirn->d_name, &filestat);
    if (!timed_) {
      timed_ = 1;
      mostrecent = filestat.st_ctime;
      mostrecentfilename = dirn->d_name;
    } else {
      if (mostrecent < filestat.st_ctime) {
        mostrecent = filestat.st_ctime;
        mostrecentfilename = dirn->d_name;
      }
    }
    //	printf("%s\n", dirn->d_name);
  }
  printf("%s\n", mostrecentfilename);
  return 0;
}
