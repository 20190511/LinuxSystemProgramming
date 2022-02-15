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
  if (remove(UNIX_DG_PATH) < 0) {
    perror("remove");
  }

  printf("\nUNIX-domain Connection-Less Server exit.....\n");

  exit(0);
}
// unix connection less - udp-like
int main(int argc, char *argv[]) {
  int servAddrLen, cliAddrLen, n;
  struct sockaddr_un cliAddr, servAddr;
  MsgType msg;

  signal(SIGINT, CloseServer);

  if ((Sockfd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
    perror("socket");  // PF_UNIX 통신
    exit(1);
  }

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sun_family = PF_UNIX;
  strcpy(servAddr.sun_path, UNIX_DG_PATH);
  servAddrLen = strlen(servAddr.sun_path) + sizeof(servAddr.sun_family);

  if (bind(Sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) <
      0) {  // binding.
    perror("bind");
    exit(1);
  }

  printf("UNIX-domain Connection-Less Server started.....\n");

  cliAddrLen = sizeof(cliAddr);  // client
  while (1) {
    if ((n = recvfrom(Sockfd, (char *)&msg, sizeof(msg), 0,
                      (struct sockaddr *)&cliAddr, &cliAddrLen)) < 0) {
      perror("recvfrom");
      exit(1);  // recieve packet.
    }
    printf("Received request: %s.....", msg.data);

    msg.type = MSG_REPLY;
    sprintf(msg.data, "This is a reply from %d.", getpid());
    if (sendto(Sockfd, (char *)&msg, sizeof(msg), 0,
               (struct sockaddr *)&cliAddr, cliAddrLen) < 0) {
      perror("sendto");
      exit(1);  // send
    }
    printf("Replied.\n");
  }
}
