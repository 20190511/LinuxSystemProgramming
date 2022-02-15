#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "sg.h"

int Sockfd;

void CloseServer() {
  close(Sockfd);
  printf("\nScatter/Gather TCP Server exit.....\n");

  exit(0);
}

int main(int argc, char *argv[]) {
  int newSockfd, cliAddrLen, n;
  struct sockaddr_in cliAddr, servAddr;
  MsgType msg;
  HeaderType hdr;
  struct iovec iov[2];
  // scatter and gather.
  signal(SIGINT, CloseServer);

  if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }  // tcp connection.

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = PF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(SERV_TCP_PORT);

  if (bind(Sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    perror("bind");
    exit(1);
  }

  listen(Sockfd, 5);  // queuing size 5

  printf("Scatter/Gather TCP Server started.....\n");

  cliAddrLen = sizeof(cliAddr);
  while (1) {
    newSockfd = accept(Sockfd, (struct sockaddr *)&cliAddr, &cliAddrLen);
    if (newSockfd < 0) {
      perror("accept");
      exit(1);
    }

    iov[0].iov_base = (char *)&hdr;  // buffer address.
    iov[0].iov_len = sizeof(hdr);    // buffer size.
    iov[1].iov_base = (char *)&msg;
    iov[1].iov_len = sizeof(msg);
    if ((n = readv(newSockfd, iov, 2)) < 0) {
      perror("read");
      exit(1);
    }
    printf("Received request: %s(%s).....", msg.data, hdr.info);

    strcpy(hdr.info, "REPLY");  // msg header.
    msg.type = MSG_REPLY;
    sprintf(msg.data, "This is a reply from %d.", getpid());
    if (writev(newSockfd, iov, 2) < 0) {
      perror("write");
      exit(1);
    }
    printf("Replied.\n");

    close(newSockfd);  // client socket close.
  }
}
