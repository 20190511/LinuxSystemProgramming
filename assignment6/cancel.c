#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t ThreadId[2];  //

void SigIntHandler(int signo) {
  int i;

  printf("Received a SIGINT signal by thread %ld\n", pthread_self());
  printf("Terminate other threads: tid=%ld, %ld\n", ThreadId[0], ThreadId[1]);

  for (i = 0; i < 2; i++) {
    /* Cancel execution of all threads */
    if (pthread_cancel(ThreadId[i])) {  // 다른 쓰레드 멈추게 하기.
      perror("pthread_cancel");
      exit(1);
    }
  }
  for (i = 0; i < 2; i++) {
    if (pthread_join(ThreadId[i], NULL)) {  // 다른 쓰레드 종료때까지 기다리기.
      perror("pthread_join");
      exit(1);
    }
  }
  printf("Threads terminated: tid=%ld, %ld\n", ThreadId[0], ThreadId[1]);

  exit(0);
}

void Thread1(void *dummy) {
  printf("Thread %ld created.....\n", pthread_self());

  if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,
                             NULL)) {  // 타 쓰레드에 의해 종료가능.
    perror("pthread_setcancelstate");
    pthread_exit(NULL);
  }
  if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,
                            NULL)) {  // 비동기적으로, 어느때나 종료 가능.
    perror("pthread_setcanceltype");
    pthread_exit(NULL);
  }

  while (1)
    ;
}

void Thread2(void *dummy) {
  printf("Thread %ld created.....\n", pthread_self());

  if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL)) {
    perror("pthread_setcancelstate");
    pthread_exit(NULL);
  }
  if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL)) {
    perror("pthread_setcanceltype");
    pthread_exit(NULL);
  }

  while (1)
    ;
}
int main() {
  if (pthread_create(&ThreadId[0], NULL, (void *)Thread1, NULL) < 0) {
    perror("pthread_create");
    exit(1);
  }
  if (pthread_create(&ThreadId[1], NULL, (void *)Thread2, NULL) < 0) {
    perror("pthread_create");
    exit(1);
  }

  signal(SIGINT, SigIntHandler);  // sigint에 대응하는 핸들러 설정.

  printf("Press ^C to quit\n");

  for (;;) pause();
}
