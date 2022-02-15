#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#include "msg.h"

#define MSG_MODE (0600)

int main() {
  int msqid, n;
  MsgType msg;

  if ((msqid = msgget(MSG_KEY, MSG_MODE)) < 0) {
    perror("msgget");
    exit(1);
  }

  msg.type = MSG_REQUEST;
  sprintf(msg.data, "This is a request from %d.", getpid());
  if (msgsnd(msqid, (char *)&msg, sizeof(msg), 0) == -1) {  // msg send
    perror("msgsnd");
    exit(1);
  }
  printf("Sent a request.....");

  if ((n = msgrcv(msqid, (char *)&msg, sizeof(msg), MSG_REPLY, 0)) == -1) {
    perror("msgrcv");  // msg_reply 인 message receive
    exit(1);
  }
  printf("Received reply: %s\n", msg.data);
}
