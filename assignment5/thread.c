#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void PrintMsg(char *msg) {
  printf("%s", msg);

  pthread_exit(NULL);
}
int main() {
  pthread_t tid1, tid2;
  char *msg1 = "Hello, ";
  char *msg2 = "World!\n";

  /* Thread ID: tid1, Thread function: PrintMsg, Thread argument: msg1 */
  // msg1을 파라미터로 가지는 printmsg라는 함수를 실행시키는 쓰레드 생성
  // tid == 쓰레드 넘버.
  if (pthread_create(&tid1, NULL, (void *)PrintMsg, (void *)msg1) < 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_create(&tid2, NULL, (void *)PrintMsg, (void *)msg2) < 0) {
    perror("pthread_create");
    exit(1);
  }

  printf("Threads created: tid=%ld, %ld\n", tid1, tid2);  // long 타입.

  /* Wait for tid1 to exit */
  // tid1, tid2 순으로 실행되기를 기다림. 에러시 0이 아님.
  if (pthread_join(tid1, NULL) < 0) {
    perror("pthread_join");
    exit(1);
  }
  if (pthread_join(tid2, NULL) < 0) {
    perror("pthread_join");
    exit(1);
  }

  printf("Threads terminated: tid=%ld, %ld\n", tid1, tid2);
}
