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
  int sockfd, n, servAddrLen, myAddrLen, peerAddrLen;
  struct sockaddr_un servAddr, myAddr, peerAddr;
  MsgType msg;

  if ((sockfd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
    perror("socket");  // client socket.
    exit(1);
  }

  bzero((char *)&myAddr, sizeof(myAddr));
  myAddr.sun_family = PF_UNIX;
  sprintf(myAddr.sun_path, ".unix-%d", getpid());
  myAddrLen = strlen(myAddr.sun_path) + sizeof(myAddr.sun_family);

  if (bind(sockfd, (struct sockaddr *)&myAddr, myAddrLen) < 0) {
    perror("bind");
    exit(1);
  }  // binding

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sun_family = PF_UNIX;
  strcpy(servAddr.sun_path, UNIX_DG_PATH);
  servAddrLen = strlen(servAddr.sun_path) + sizeof(servAddr.sun_family);

  msg.type = MSG_REQUEST;
  sprintf(msg.data, "This is a request from %d.", getpid());
  if (sendto(sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&servAddr,
             servAddrLen) < 0) {
    perror("sendto");
    exit(1);
  }  // send to server
  printf("Sent a request.....");

  peerAddrLen = sizeof(peerAddr);
  if ((n = recvfrom(sockfd, (char *)&msg, sizeof(msg), 0,
                    (struct sockaddr *)&peerAddr, &peerAddrLen)) < 0) {
    perror("recvfrom");
    exit(1);
  }
  printf("Received reply: %s\n", msg.data);

  close(sockfd);  // socket close.
  if (remove(myAddr.sun_path) < 0) {
    perror("remove");
    exit(1);
  }  // file delete
}
