#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#include "msg.h"

#define MSG_MODE (0600 | IPC_CREAT)
// rw-------, CREATE.

int main() {
  int msqid, n;
  MsgType msg;

  if ((msqid = msgget(MSG_KEY, MSG_MODE)) <
      0) {  // msg_key에 상응하는 메시지 큐 받기
    perror("msgget");
    exit(1);
  }

  if ((n = msgrcv(msqid, (void *)&msg, sizeof(MsgType), 0, 0)) ==
      -1) {  // receiving.
    perror("msgrcv");
    exit(1);
  }
  printf("Received request: %s.....", msg.data);

  msg.type = MSG_REPLY;
  char rep[256];
  sprintf(rep, "This is a reply from %d.", getpid());
  strcpy(msg.data, rep);
  if (msgsnd(msqid, (void *)&msg, sizeof(MsgType), 0) == -1) {  // sending.
    perror("msgsnd");
    exit(1);
  }
  printf("Replied.\n");

  sleep(1);

  /* Remove message queue */
  if (msgctl(msqid, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    exit(1);
  }  // IPC_REMOVE ID
}
