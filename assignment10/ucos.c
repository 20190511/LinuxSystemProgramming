#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include "unix.h"

int Sockfd;

void CloseServer() {
  close(Sockfd);
  if (remove(UNIX_STR_PATH) < 0) {
    perror("remove");
  }

  printf("\nUNIX-domain Connection-Oriented Server exit.....\n");

  exit(0);
}

int main(int argc, char *argv[]) {
  int newSockfd, servAddrLen, cliAddrLen, n;
  struct sockaddr_un cliAddr, servAddr;
  MsgType msg;

  signal(SIGINT, CloseServer);

  if ((Sockfd = (socket(PF_UNIX, SOCK_STREAM, 0))) < 0) {
    perror("socket");
    exit(1);
  }  // UNIX 방식 + TCP

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sun_family = PF_UNIX;
  strcpy(servAddr.sun_path, UNIX_STR_PATH);
  servAddrLen = strlen(servAddr.sun_path) + sizeof(servAddr.sun_family);

  if (bind(Sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    perror("bind");
    exit(1);
  }  // 바인딩.

  listen(Sockfd, 0);

  printf("UNIX-domain Connection-Oriented Server started.....\n");

  cliAddrLen = sizeof(cliAddr);
  while (1) {
    newSockfd = accept(Sockfd, (struct sockaddr *)&cliAddr, &cliAddrLen);
    if (newSockfd < 0) {
      perror("accept");
      exit(1);
    }

    if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0) {
      perror("read");
      exit(1);
    }  // 수신
    printf("Received request: %s.....", msg.data);

    msg.type = MSG_REPLY;
    sprintf(msg.data, "This is a reply from %d.", getpid());
    if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0) {
      perror("write");
      exit(1);
    }  // 전송
    printf("Replied.\n");

    close(newSockfd);
  }
}
