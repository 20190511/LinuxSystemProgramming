#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "tcp.h"

int main(int argc, char *argv[]) {
  int sockfd, n;
  struct sockaddr_in servAddr;
  MsgType msg;
  struct hostent *hp;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s IPaddress\n", argv[0]);
    exit(1);
  }  // get ip address as param.

  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }  // tcp connection.

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = PF_INET;
  servAddr.sin_port = htons(SERV_TCP_PORT);

  if (isdigit(argv[1][0])) {  // ip address or domain name?
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
  } else {
    if ((hp = gethostbyname(argv[1])) == NULL) {
      fprintf(stderr, "Unknown host: %s\n", argv[1]);
      exit(1);
    }
    memcpy(&servAddr.sin_addr, hp->h_addr, hp->h_length);
  }

  if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    perror("connect");
    exit(1);
  }  // connect to server

  msg.type = MSG_REQUEST;
  sprintf(msg.data, "This is a request from %d.", getpid());
  if (write(sockfd, (char *)&msg, sizeof(msg)) < 0) {
    perror("write");
    exit(1);
  }  // send
  printf("Sent a request.....");

  if ((n = read(sockfd, (char *)&msg, sizeof(msg))) < 0) {
    perror("read");
    exit(1);
  }  // recieve
  printf("Received reply: %s\n", msg.data);

  close(sockfd);
}
