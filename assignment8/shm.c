#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE (SHM_R | SHM_W)

char Array[ARRAY_SIZE];  // 데이터 영역
int main() {
  int shmid;  // 스택 영역
  char *ptr, *shmptr;

  if ((ptr = (char *)malloc(MALLOC_SIZE)) == NULL) {  // 동적 할당. 힙 영역
    perror("malloc");
    exit(1);
  }

  if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0) {
    perror("shmget");
    exit(1);
  }
  if ((shmptr = shmat(shmid, 0, 0)) == (void *)-1) {  // 그 사이
    perror("shmat");
    exit(1);
  }

  printf("Array[] from %p to %p\n", &Array[0],
         &Array[ARRAY_SIZE]);           // 데이터 영역. 가장 낮음
  printf("Stack around %p\n", &shmid);  // 가장 높음
  printf("Malloced from %p to %p\n", ptr,
         ptr + MALLOC_SIZE);  // 데이터 영역 보단 높음
  printf("Shared memory attached from %p to %p\n", shmptr,
         shmptr + SHM_SIZE);  // 힙과 스택 사이

  if (shmdt(shmptr) < 0) {
    perror("shmdt");
    exit(1);
  }

  if (shmctl(shmid, IPC_RMID, 0) < 0) {
    perror("shmctl");
    exit(1);
  }
}
