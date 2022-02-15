#include <arpa/inet.h>
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
  strcpy(msg.data, "");
  if (argc >= 3)
    for (int i = 2; i < argc; i++) {
      strcat(msg.data, argv[i]);
      strcat(msg.data, " ");
    }
  msg.type = MSG_REQUEST;
  char clientCommand[100];

  if (write(sockfd, (char *)&msg, sizeof(msg)) < 0) {  // 서버에 전송
    perror("write");
    exit(1);
  }
  if ((n = read(sockfd, (char *)&msg, sizeof(msg))) < 0) {  // read like file.
    perror("read");
    exit(1);
  }
  printf("%s\n", msg.data);

  close(sockfd);
}
