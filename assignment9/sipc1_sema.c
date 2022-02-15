#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
// #include "shm.h"
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
  }  // shared mem get
  if ((ptr = shmat(shmid, 0, 0)) == (void *)-1) {
    perror("shmat");
    exit(1);
  }
  if ((sendingSemid = semInit(FULL_SEM_KEY)) < 0) {
    fprintf(stderr, "semInit failure\n");
    exit(1);
  }
  if ((gettingSemid = semInit(EMPTY_SEM_KEY)) < 0) {
    fprintf(stderr, "semInit failure\n");
    exit(1);
  }
  /*
  while ((*pInt) == 0) // pInt가 변경될 때까지 기다림
          ;
  */

  if (semWait(sendingSemid) < 0)  // wait until getter got Send.
  {
    fprintf(stderr, "semWait failure\n");
    exit(1);
  }

  printf("Received request: %s.....", ptr);
  sprintf(ptr, "This is a reply from %d.", getpid());
  printf("Replied.\n");
  if (semPost(gettingSemid) < 0)  // 받았음을 sipc2의 semaphore에 signal.
  {
    fprintf(stderr, "semPost failure\n");
    exit(1);
  }

  sleep(1);  // sipc1에서 semaphore 해체.
  if (semDestroy(gettingSemid) < 0) {
    fprintf(stderr, "semDestroy failure\n");
  }
  if (semDestroy(sendingSemid) < 0) {
    fprintf(stderr, "semDestroy failure\n");
  }

  /* Detach shared memory */
  if (shmdt(ptr) == -1) {
    perror("shmdt");
    exit(1);
  }

  /* Remove shared memory */
  if (shmctl(shmid, IPC_RMID, 0) == -1) {
    perror("shmctl");
    exit(1);
  }
}
