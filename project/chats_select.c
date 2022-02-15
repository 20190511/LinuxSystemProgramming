#include <arpa/inet.h>
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

#define DEBUG

#define MAX_CLIENT 5
#define MAX_ID 32
#define MAX_BUF 256

typedef struct {
  int sockfd;
  int inUse;
  pthread_t tid;
  char uid[MAX_ID];
} ClientType;

int Sockfd;
pthread_mutex_t Mutex;

ClientType Client[MAX_CLIENT];

int GetID() {
  int i;

  for (i = 0; i < MAX_CLIENT; i++) {
    if (!Client[i].inUse) {
      Client[i].inUse = 1;
      return i;
    }
  }
}

void SendToOtherClients(int id, char *buf) {
  int i;
  char msg[MAX_BUF + MAX_ID];

  sprintf(msg, "%s> %s", Client[id].uid, buf);
#ifdef DEBUG
  printf("%s", msg);
  fflush(stdout);
#endif

  pthread_mutex_lock(&Mutex);
  for (i = 0; i < MAX_CLIENT; i++) {
    if (Client[i].inUse && (i != id)) {
      if (send(Client[i].sockfd, msg, strlen(msg) + 1, 0) < 0) {
        perror("send");
        exit(1);
      }
    }
  }
  pthread_mutex_unlock(&Mutex);
}

void CloseServer(int signo) {
  int i;

  close(Sockfd);

  for (i = 0; i < MAX_CLIENT; i++) {
    if (Client[i].inUse) {
      close(Client[i].sockfd);
    }
  }
  if (pthread_mutex_destroy(&Mutex) < 0) {
    perror("pthread_mutex_destroy");
    exit(1);
  }

  printf("\nChat server terminated.....\n");

  exit(0);
}
int main(int argc, char *argv[]) {
  int newSockfd, cliAddrLen, count, id, one = 1;
  struct sockaddr_in cliAddr, servAddr;
  fd_set myfdset;
  signal(SIGINT, CloseServer);
  if (pthread_mutex_init(&Mutex, NULL) < 0) {
    perror("pthread_mutex_init");
    exit(1);
  }

  if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }

  if (setsockopt(Sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0) {
    perror("setsockopt");
    exit(1);
  }

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = PF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(SERV_TCP_PORT);

  if (bind(Sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    perror("bind");
    exit(1);
  }

  listen(Sockfd, 5);

  printf("Chat server started.....\n");

  cliAddrLen = sizeof(cliAddr);
  while (1) {
    FD_ZERO(&myfdset);
    FD_SET(Sockfd, &myfdset);
    for (int i = 0; i < MAX_CLIENT; i++) {
      if (Client[i].inUse) FD_SET(Client[i].sockfd, &myfdset);
    }
    if ((count = select(10, &myfdset, NULL, NULL, NULL)) < 0) {
      perror("select");
      exit(1);
    }
    while (count--) {
      if (FD_ISSET(Sockfd, &myfdset)) {
        newSockfd = accept(Sockfd, (struct sockaddr *)&cliAddr, &cliAddrLen);
        if (newSockfd < 0) {
          perror("accept");
          exit(1);
        }
        id = GetID();
        Client[id].sockfd = newSockfd;
        int n;
        if ((n = recv(Client[id].sockfd, Client[id].uid, MAX_ID, 0)) < 0) {
          perror("recv");
          exit(1);
        }
        printf("Client %d log-in(ID: %s).....\n", id, Client[id].uid);
        FD_SET(newSockfd, &myfdset);
      } else {
        for (int i = 0; i < MAX_CLIENT; i++) {
          if (Client[i].inUse) {
            char tempBuf[MAX_BUF];
            int tempN;
            if (FD_ISSET(Client[i].sockfd, &myfdset)) {
              if ((tempN = recv(Client[i].sockfd, tempBuf, MAX_BUF, 0)) < 0) {
                perror("recv");
                exit(1);
              }
              if (tempN == 0) {
                printf("Client %d log-out(ID: %s).....\n", i, Client[i].uid);

                pthread_mutex_lock(&Mutex);
                FD_CLR(Client[i].sockfd, &myfdset);
                close(Client[i].sockfd);
                Client[i].inUse = 0;
                pthread_mutex_unlock(&Mutex);

                strcpy(tempBuf, "log-out.....\n");
                SendToOtherClients(i, tempBuf);
              } else
                SendToOtherClients(i, tempBuf);
            }
          }
        }
      }
    }
    // if (pthread_create(&Client[id].tid, NULL, (void *)ProcessClient, (void
    // *)&id) < 0)  { 	perror("pthread_create"); 	exit(1);
    // }
  }
}
