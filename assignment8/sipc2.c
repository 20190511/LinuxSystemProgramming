#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#include "shm.h"

int main() {
  int shmid;
  char *ptr, *pData;
  int *pInt;

  /* SHM_KEY, SHM_SIZE, SHM_MODE in shm.h */
  if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) == -1) {
    perror("shmget");
    exit(1);
  }
  if ((ptr = shmat(shmid, 0, 0)) == (void *)-1) {
    perror("shmat");
    exit(1);
  }

  pInt = (int *)ptr;
  pData = ptr + sizeof(int);  // 상태를 나타내는 int만큼 건너뛰기
  sprintf(pData, "This is a request from %d.", getpid());
  *pInt = 1;  // shared mem의 상태를 바꿔서 다른 프로세스와 통신, IPC.
  printf("Sent a request.....");

  while ((*pInt) == 1)  // 0으로 바꿀 때까지 기다림.
    ;

  printf("Received reply: %s\n", pData);

  /* Detach shared memory */
  if (shmdt(ptr) == -1) {
    perror("shmdt");
    exit(1);
  }
}
