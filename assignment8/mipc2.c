#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/types.h>

#include "shm.h"
#include "synclib.h"

#define NLOOPS 10
#define SIZE sizeof(long)

int update(long *ptr) { return ((*ptr)++); }
int main() {
  int fd, i, counter;
  pid_t pid;
  int shmid;
  long *ptr;
  long *pData;
  // define in shm.h
  if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) == -1) {
    perror("shmget");
    exit(1);
  }
  if ((ptr = shmat(shmid, 0, 0)) == (void *)-1) {
    perror("shmat");
    exit(1);
  }

  TELL_WAIT();  // 동기화용
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid > 0) {
    for (i = 0; i < NLOOPS; i += 2) {
      if ((counter = update(ptr)) != i) {
        fprintf(stderr, "Counter mismatch\n");
        exit(1);
      }
      printf("Parent: counter=%d\n", counter);
      TELL_CHILD();
      WAIT_CHILD();  // 자식의TELL_PARENT 기다리기
    }
  } else {
    for (i = 1; i < NLOOPS; i += 2) {
      WAIT_PARENT();  // 부모 먼저
      if ((counter = update(ptr)) != i) {
        fprintf(stderr, "Counter mismatch\n");
        exit(1);
      }
      printf("Child : counter=%d\n", counter);
      TELL_PARENT();
    }
  }
  if (shmdt(ptr) == -1) {
    perror("shmdt");
    exit(1);
  }
  if (pid != 0 && shmctl(shmid, IPC_RMID, 0) == -1) {
    perror("shmctl");
    exit(1);
  }
}
