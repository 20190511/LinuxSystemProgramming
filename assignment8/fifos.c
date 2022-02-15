#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "fifo.h"  // SERV_FIFO 매크로.

void SigIntHandler(int signo) {
  if (remove(SERV_FIFO) < 0) {  // 만든 fifo 삭제
    perror("remove");
    exit(1);
  }

  exit(0);
}

// 서버 측 fifo.
int main() {
  int fd, cfd, n;
  MsgType msg;

  if (signal(SIGINT, SigIntHandler) == SIG_ERR) {
    perror("signal");
    exit(1);
  }  // interrupt 발생 시 fifo 삭제 핸들러 추가.

  if (mkfifo(SERV_FIFO, 0600) < 0) {  // rwx권한이 110-000-000.
    if (errno != EEXIST) {            // 생성후 에러 확인
      perror("mkfifo");
      exit(1);
    }
  }

  if ((fd = open(SERV_FIFO, O_RDWR)) < 0) {  // READ WRITE로 fifo 열기
    perror("open");
    exit(1);
  }

  while (1) {
    if ((n = read(fd, (char *)&msg, sizeof(msg))) < 0) {  //  msg를 읽기 대기
      if (errno == EINTR) {  // 인터럽트 시 에러가 아님
        continue;
      } else {
        perror("read");
        exit(1);
      }
    }
    printf("Received request: %s.....", msg.data);

    if ((cfd = open(msg.returnFifo, O_WRONLY)) < 0) {  // 반환 fifo 지정
      perror("open");
      exit(1);
    }
    sprintf(msg.data, "This is a reply from %d.", getpid());
    write(cfd, (char *)&msg, sizeof(msg));  // 반환 fifo로 메시지 전송.
    close(cfd);                             //
    printf("Replied.\n");
  }
}
