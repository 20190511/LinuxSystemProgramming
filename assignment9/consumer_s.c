#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#include "prodcons.h"
#include "semlib.h"
int main() {
  BoundedBufferType *pBuf;
  int shmid, i, data;
  int emptySemid, fullSemid, mutexSemid;

  if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) <
      0) {  // shared with producer
    perror("shmget");
    exit(1);
  }
  if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *)-1) {
    perror("shmat");
    exit(1);
  }

  if ((emptySemid = semInit(EMPTY_SEM_KEY)) < 0) {
    fprintf(stderr, "semInit failure\n");
    exit(1);
  }
  if ((fullSemid = semInit(FULL_SEM_KEY)) < 0) {
    fprintf(stderr, "semInit failure\n");
    exit(1);
  }
  if ((mutexSemid = semInit(MUTEX_SEM_KEY)) < 0) {
    fprintf(stderr, "semInit failure\n");
    exit(1);
  }

  if (semInitValue(emptySemid, MAX_BUF) < 0) {  // empty = N
    fprintf(stderr, "semInitValue failure\n");
    exit(1);
  }
  if (semInitValue(fullSemid, 0) < 0) {  // full = 0
    fprintf(stderr, "semInitValue failure\n");
    exit(1);
  }
  if (semInitValue(mutexSemid, 1) < 0) {  // mutex = 1
    fprintf(stderr, "semInitValue failure\n");
    exit(1);
  }

  srand(0x9999);
  for (i = 0; i < NLOOPS; i++) {
    if (semWait(fullSemid) < 0) {  // wait until full > 0
      fprintf(stderr, "semWait failure\n");
      exit(1);
    }
    if (semWait(mutexSemid) < 0) {
      fprintf(stderr, "semWait failure\n");
      exit(1);
    }
    printf("Consumer: Consuming an item.....\n");
    data = pBuf->buf[pBuf->out].data;
    pBuf->out = (pBuf->out + 1) % MAX_BUF;
    pBuf->counter--;

    if (semPost(mutexSemid) < 0) {
      fprintf(stderr, "semPost failure\n");
      exit(1);
    }
    if (semPost(emptySemid) < 0) {  // empty+=1
      fprintf(stderr, "semPost failure\n");
      exit(1);
    }

    usleep((rand() % 100) * 10000);
  }

  printf("Consumer: Consumed %d items.....\n", i);
  printf("Consumer: %d items in buffer.....\n", pBuf->counter);
}
