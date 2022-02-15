#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "chat.h"

#define MAX_BUF 256

int Sockfd;
char buf[MAX_BUF];
int n;
void getChat(void *dummy) {
  while (1) {
    if ((n = recv(Sockfd, buf, MAX_BUF, 0)) < 0) {
      perror("recv");
      exit(1);
    }
    if (n == 0) {
      fprintf(stderr, "Server terminated.....\n");
      close(Sockfd);
      exit(0);
    }
    printf("%s", buf);
  }
  pthread_exit(NULL);
}

void putChat(void *dummy) {
  while (1) {
    fgets(buf, MAX_BUF, stdin);
    if ((n = send(Sockfd, buf, strlen(buf) + 1, 0)) < 0) {
      perror("send");
      exit(1);
    }
  }
  pthread_exit(NULL);
}

void ChatClient(void) {
  printf("Enter ID: ");
  fflush(stdout);
  fgets(buf, MAX_BUF, stdin);
  *strchr(buf, '\n') = '\0';
  if (send(Sockfd, buf, strlen(buf) + 1, 0) < 0) {
    perror("send");
    exit(1);
  }
  printf("Press ^C to exit\n");
  pthread_t gtid, ptid;
  if (pthread_create(&gtid, NULL, (void *)getChat, NULL) < 0) {
    perror("pthread_create");
    exit(1);
  }
  if (pthread_create(&ptid, NULL, (void *)putChat, NULL) < 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_join(gtid, NULL) < 0) {
    perror("pthread_join");
    exit(1);
  }
  if (pthread_join(ptid, NULL) < 0) {
    perror("pthread_join");
    exit(1);
  }
}

void CloseClient(int signo) {
  close(Sockfd);
  printf("\nChat client terminated.....\n");

  exit(0);
}

int main(int argc, char *argv[]) {
  struct sockaddr_in servAddr;
  struct hostent *hp;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s ServerIPaddress\n", argv[0]);
    exit(1);
  }

  if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = PF_INET;
  servAddr.sin_port = htons(SERV_TCP_PORT);

  if (isdigit(argv[1][0])) {
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
  } else {
    if ((hp = gethostbyname(argv[1])) == NULL) {
      fprintf(stderr, "Unknown host: %s\n", argv[1]);
      exit(1);
    }
    memcpy(&servAddr.sin_addr, hp->h_addr, hp->h_length);
  }

  if (connect(Sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    perror("connect");
    exit(1);
  }

  signal(SIGINT, CloseClient);

  ChatClient();
}
