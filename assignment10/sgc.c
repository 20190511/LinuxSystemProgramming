#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "sg.h"

int main(int argc, char *argv[]) {
  int sockfd, n;
  struct sockaddr_in servAddr;
  MsgType msg;
  HeaderType hdr;
  struct iovec iov[2];

  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }  // open socket.

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = PF_INET;
  servAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
  servAddr.sin_port = htons(SERV_TCP_PORT);

  if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    perror("connect");
    exit(1);
  }  // connection to server

  strcpy(hdr.info, "REQST");
  msg.type = MSG_REQUEST;
  sprintf(msg.data, "This is a request from %d.", getpid());
  iov[0].iov_base = (char *)&hdr;
  iov[0].iov_len = sizeof(hdr);
  iov[1].iov_base = (char *)&msg;
  iov[1].iov_len = sizeof(msg);
  if (writev(sockfd, iov, 2) < 0) {  // send scattered data.
    perror("write");
    exit(1);
  }
  printf("Sent a request.....");

  if ((n = readv(sockfd, iov, 2)) < 0) {
    perror("read");
    exit(1);
  }
  printf("Received reply: %s(%s)\n", msg.data, hdr.info);

  close(sockfd);  // close socket.
}
