#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "synclib.h"

#define NLOOPS 10
#define SIZE sizeof(long)

int update(long *ptr) { return ((*ptr)++); }
int main() {
  int fd, i, counter;
  pid_t pid;
  caddr_t area;

  if ((fd = open("/dev/zero", O_RDWR)) < 0) {
    perror("open");
    exit(1);
  }
  if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) ==
      (caddr_t)-1) {
    perror("mmap");
    exit(1);
  }  // mmap을 이용해서 memory-mapped file >> IPC.
  // PROT - rw, MAP_SHARED - mapped file을 변경, fd에 있는 파일로 덮어씀.
  close(fd);

  TELL_WAIT();  // 동기화용
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid > 0) {
    for (i = 0; i < NLOOPS; i += 2) {
      if ((counter = update((long *)area)) != i) {
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
      if ((counter = update((long *)area)) != i) {
        fprintf(stderr, "Counter mismatch\n");
        exit(1);
      }
      printf("Child : counter=%d\n", counter);
      TELL_PARENT();
    }
  }
}
