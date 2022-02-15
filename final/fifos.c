#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int fd, n;
typedef struct {
  char username[100];
  char body[100];
} mymsg;

void sigHand() {
  if (remove("./myfifo") < 0) {
    perror("remove");
    exit(1);
  }
  if (close(fd) < 0) {
    perror("close");
    exit(1);
  }
  exit(0);
}

int main() {
  signal(SIGINT, sigHand);
  if (mkfifo("./myfifo", 0600) < 0) {
    perror("mkfifo");
    exit(1);
  }
  mymsg msg;
  if ((fd = open("./myfifo", O_RDWR)) < 0) {
    perror("open");
    exit(1);
  }
  while (1) {
    if ((n = read(fd, (char *)&msg, sizeof(msg))) < 0) {
      perror("read");
      exit(1);
    }
    char filename[100];
    strcpy(filename, msg.username);
    FILE *userfile;
    if ((userfile = fopen(filename, "at")) == NULL) {
      perror("fopen");
      exit(1);
    }
    int charptr = 0;
    while (msg.body[charptr] != '\0') {
      putc(msg.body[charptr], userfile);
      charptr++;
    }
    putc('\n', userfile);
    fclose(userfile);
  }
}
