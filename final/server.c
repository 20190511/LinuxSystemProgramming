#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "tcp.h"

int Sockfd;

void CloseServer() {
  close(Sockfd);

  exit(0);
}

int main(int argc, char *argv[]) {
  int newSockfd, cliAddrLen, n;
  struct sockaddr_in cliAddr, servAddr;
  MsgType msg;

  signal(SIGINT, CloseServer);  // signal handler 설정

  if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {  // tcp 설정
    perror("socket");
    exit(1);
  }  // socket descriptor 반환

  bzero((char *)&servAddr, sizeof(servAddr));  // 메모리를 0으로.
  servAddr.sin_family = PF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(SERV_TCP_PORT);
  // 서버 주소 설정.
  if (bind(Sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) <
      0) {  // binding
    perror("bind");
    exit(1);
  }

  listen(Sockfd, 5);  // listening.

  cliAddrLen = sizeof(cliAddr);

  while (1) {
    newSockfd = accept(Sockfd, (struct sockaddr *)&cliAddr, &cliAddrLen);
    // wait until accepts.
    if (newSockfd < 0) {
      perror("accept");
      exit(1);
    }
    pid_t clientPID;
    clientPID = fork();  // fork child process.
    if (clientPID < 0) {
      perror("fork");
      exit(1);
    } else if (clientPID == 0) {
      if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) <
          0) {  // read like file.
        perror("read");
        exit(1);
      }
      msg.type = MSG_REPLY;
      char clientCommand[100];
      strcpy(clientCommand, msg.data);
      system(clientCommand);
      exit(0);  // child process terminated
    } else {
      wait(NULL);
      strcpy(msg.data, "Done");
      if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0) {  // send.
        perror("write");
        exit(1);
      }
    }
    usleep(10000);
    close(newSockfd);  // close connection.
  }
}
