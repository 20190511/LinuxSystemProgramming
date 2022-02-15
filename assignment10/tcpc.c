#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "tcp.h"

int main(int argc, char *argv[]) {
  int sockfd, n;
  struct sockaddr_in servAddr;
  MsgType msg;

  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {  // 소켓 설정
    perror("socket");
    exit(1);
  }

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = PF_INET;
  servAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
  servAddr.sin_port = htons(SERV_TCP_PORT);

  if (connect(sockfd, (struct sockaddr *)(&servAddr), sizeof(servAddr)) < 0) {
    perror("connect");  // 서버와 연결: TCP.
    exit(1);
  }

  msg.type = MSG_REQUEST;
  sprintf(msg.data, "This is a request from %d.", getpid());
  if (write(sockfd, (char *)&msg, sizeof(msg)) < 0) {  // 서버에 전송
    perror("write");
    exit(1);
  }
  printf("Sent a request.....");

  if ((n = read(sockfd, (char *)&msg, sizeof(msg))) <
      0) {  // 서버에서 데이터 받기.
    perror("read");
    exit(1);
  }
  printf("Received reply: %s\n", msg.data);

  close(sockfd);
}
