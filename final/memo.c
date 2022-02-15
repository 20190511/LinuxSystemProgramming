#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
  char username[100];
  char body[100];
} mymsg;

int main(int argc, char* argv[]) {
  int fd, n;
  mymsg msg;
  if (argc == 2) {
    char executing[100];
    sprintf(executing, "cat %s", argv[1]);
    system(executing);
  } else if (argc >= 3) {
    if ((fd = open("./myfifo", O_RDWR)) < 0) {
      perror("open");
      exit(1);
    }
    strcpy(msg.username, argv[1]);
    strcpy(msg.body, "");
    for (int i = 2; i < argc; i++) {
      strcat(msg.body, argv[i]);
      strcat(msg.body, " ");
    }
    if (write(fd, (char*)&msg, sizeof(msg)) < 0) {
      perror("write");
      exit(1);
    }
  }
}
