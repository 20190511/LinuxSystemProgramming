#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define MAX_BUF 1024

int main(void) {
  DIR *dp;
  struct dirent *dirn;
  struct stat buf;
  char mode_char[10] = "rwxrwxrwx";
  if ((dp = opendir(".")) == 0) {
    perror("opendir");
    exit(1);
  }
  while (dirn = readdir(dp)) {
    char dirname[MAX_BUF] = "";
    struct passwd *pwd;
    struct group *g;
    strcat(dirname, dirn->d_name);

    if (lstat(dirname, &buf) < 0) {
      perror("lstat");
      exit(1);
    }

    pwd = getpwuid(buf.st_uid);
    g = getgrgid(buf.st_gid);

    char currmode[11] = "----------";
    int cumod = buf.st_mode;

    for (int i = 8; i >= 0; i--)
      if ((1 << i) & cumod) currmode[8 - i] = mode_char[8 - i];
    for (int i = 9; i >= 1; i--) currmode[i] = currmode[i - 1];

    if (S_ISREG(buf.st_mode))
      currmode[0] = '-';
    else if (S_ISDIR(buf.st_mode))
      currmode[0] = 'd';
    else if (S_ISCHR(buf.st_mode))
      currmode[0] = 'c';
    else if (S_ISBLK(buf.st_mode))
      currmode[0] = 'b';
    else if (S_ISLNK(buf.st_mode))
      currmode[0] = 'l';
    char *lastChangedTime = asctime(gmtime(&buf.st_ctime));
    lastChangedTime[strlen(lastChangedTime) - 1] = '\0';

    printf("%-15s", dirn->d_name);
    printf("%-5ld", buf.st_nlink);
    printf("%-30s", lastChangedTime);
    printf("%-12s", currmode);
    printf("%-10s", pwd->pw_name);
    printf("%-10s", g->gr_name);
    printf("%-10ld\n", buf.st_size);
  }

  return 0;
}
