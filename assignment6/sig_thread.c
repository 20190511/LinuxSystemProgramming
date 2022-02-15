#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_MAIN
// define에 따라 달라짐.
/*
#define	THREAD_1
#define	THREAD_2
*/

void SigIntHandler(int signo) {
  printf("Received a SIGINT signal by thread %ld\n",
         pthread_self());  // tid호출
  printf("Terminate this process\n");

  exit(0);
}

void Thread1(void *dummy) {
#ifdef THREAD_1
  signal(SIGINT, SigIntHandler);
#endif

  while (1)
    ;
}

void Thread2(void *dummy) {
#ifdef THREAD_2
  signal(SIGINT, SigIntHandler);
#endif

  while (1)
    ;
}
int main() {
  pthread_t tid1, tid2;

  if (pthread_create(&tid1, NULL, (void *)Thread1, NULL) < 0) {
    perror("pthread_create");
    exit(1);
  }
  if (pthread_create(&tid2, NULL, (void *)Thread2, NULL) < 0) {
    perror("pthread_create");
    exit(1);
  }
  // sigint에 호출되는 핸들러를 가지는 쓰레드 두개 생성.
  printf("Create two threads: tid1=%ld, tid2=%ld\n", tid1, tid2);
  printf("Main thread: tid=%ld\n", pthread_self());
#ifdef THREAD_MAIN
  signal(SIGINT, SigIntHandler);  // 메인 쓰레드에서 핸들러 호출됨.
#endif

  printf("Press ^C to quit\n");
  // 스레드끼리 signal이 공유됨.
  for (;;) pause();
}
