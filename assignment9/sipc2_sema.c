#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
// #include "shm.h"
#include <sys/sem.h>

#include "prodcons.h"
#include "semlib.h"

int main() {
  int shmid;
  char *ptr;
  key_t sendingSemid, gettingSemid;

  /* SHM_KEY, SHM_SIZE, SHM_MODE in shm.h */
  if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) == -1) {
    perror("shmget");
    exit(1);
  }
  if ((ptr = shmat(shmid, 0, 0)) == (void *)-1) {
    perror("shmat");
    exit(1);
  }
  if ((sendingSemid = semInit(FULL_SEM_KEY)) < 0) {  // 보내는 측의 semaphore.
    fprintf(stderr, "semInit failure\n");
    exit(1);
  }
  if ((gettingSemid = semInit(EMPTY_SEM_KEY)) < 0) {  // 받는 측의 semaphore
    fprintf(stderr, "semInit failure\n");
    exit(1);
  }
  if (semPost(sendingSemid) < 0) {
    fprintf(stderr, "semPost failure\n");
    exit(1);
  }
  sprintf(ptr, "This is a request from %d.", getpid());
  printf("Sent a request.....");

  /*
  while ((*pInt) == 1) // 0으로 바꿀 때까지 기다림.
          ;
  */
  if (semWait(gettingSemid) < 0) {
    fprintf(stderr, "semWait failure\n");
    exit(1);
  }

  printf("Received reply: %s\n", ptr);

  /* Detach shared memory */
  if (shmdt(ptr) == -1) {
    perror("shmdt");
    exit(1);
  }
}
