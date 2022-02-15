#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "fifo.h"

int main() {
  char fname[MAX_FIFO_NAME];
  int fd, sfd, n;
  MsgType msg;

  sprintf(fname, ".fifo%d", getpid());  // fifo 생성용 이름
  if (mkfifo(fname, 0600) < 0) {        // fifo 생성
    perror("mkfifo");
    exit(1);
  }

  if ((fd = open(fname, O_RDWR)) < 0) {  // read write
    perror("open");
    exit(1);
  }
  if ((sfd = open(SERV_FIFO, O_RDWR)) < 0) {  // server fifo
    perror("open");
    exit(1);
  }

  strcpy(msg.returnFifo, fname);  // 반환 받을 fifo 입력
  sprintf(msg.data, "This is a request from %d.", getpid());
  write(sfd, &msg, sizeof(msg));
  printf("Sent a request.....");

  if (read(fd, &msg, sizeof(msg)) == -1) {
    perror("read");
    exit(1);
  }

  printf("Received reply: %s\n", msg.data);

  close(fd);
  close(sfd);

  /* Remove temporary FIFO */
  if (remove(fname) == -1) {
    perror("remove");
    exit(1);
  }
}
