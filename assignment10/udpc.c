#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "udp.h"

int main(int argc, char *argv[]) {
  int sockfd, n, peerAddrLen;
  struct sockaddr_in servAddr, peerAddr;
  MsgType msg;

  if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }  // UDP - connectionless.

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = PF_INET;
  servAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
  servAddr.sin_port = htons(SERV_UDP_PORT);

  msg.type = MSG_REQUEST;
  sprintf(msg.data, "This is a request from %d.", getpid());
  if ((sendto(sockfd, (char *)&msg, sizeof(msg), 0,  // send packet.
              (struct sockaddr *)&servAddr, sizeof(servAddr))) < 0) {
    perror("sendto");
    exit(1);
  }
  printf("Sent a request.....");

  peerAddrLen = sizeof(peerAddr);
  if ((n = recvfrom(sockfd, (char *)&msg, sizeof(msg), 0,  // recieve
                    (struct sockaddr *)&peerAddr, &peerAddrLen)) < 0) {
    perror("recvfrom");
    exit(1);
  }
  printf("Received reply: %s\n", msg.data);

  close(sockfd);
}
