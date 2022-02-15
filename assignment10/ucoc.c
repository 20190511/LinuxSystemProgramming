#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include "unix.h"

int main(int argc, char *argv[]) {
  int sockfd, n, servAddrLen;
  struct sockaddr_un servAddr;
  MsgType msg;

  if ((sockfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {  // socket 생성.
    perror("socket");
    exit(1);
  }

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sun_family = PF_UNIX;  // unix 방식.
  strcpy(servAddr.sun_path, UNIX_STR_PATH);
  servAddrLen = strlen(servAddr.sun_path) + sizeof(servAddr.sun_family);

  if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    perror("connect");
    exit(1);
  }

  msg.type = MSG_REQUEST;
  sprintf(msg.data, "This is a request from %d.", getpid());
  if (write(sockfd, (char *)&msg, sizeof(msg)) < 0) {  // 전송
    perror("write");
    exit(1);
  }
  printf("Sent a request.....");

  if ((n = read(sockfd, (char *)&msg, sizeof(msg))) < 0) {  // 수신
    perror("read");
    exit(1);
  }
  printf("Received reply: %s\n", msg.data);

  close(sockfd);
}
