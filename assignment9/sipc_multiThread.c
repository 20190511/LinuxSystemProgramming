#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "prodcons.h"
#include "semlib2.h"

int buffer;
pthread_cond_t Sender;
pthread_cond_t Getter;
pthread_mutex_t Mutex;

sem_t mutexSem, SSem, GSem;

void ThreadUsleep(int usecs) {
  pthread_cond_t cond;
  pthread_mutex_t mutex;
  struct timespec ts;
  struct timeval tv;

  if (pthread_cond_init(&cond, NULL) < 0) {
    perror("pthread_cond_init");
    pthread_exit(NULL);
  }
  if (pthread_mutex_init(&mutex, NULL) < 0) {
    perror("pthread_mutex_init");
    pthread_exit(NULL);
  }

  gettimeofday(&tv, NULL);
  ts.tv_sec = tv.tv_sec + usecs / 1000000;
  ts.tv_nsec = (tv.tv_usec + (usecs % 1000000)) * 1000;
  if (ts.tv_nsec >= 1000000000) {
    ts.tv_nsec -= 1000000000;
    ts.tv_sec++;
  }

  if (pthread_mutex_lock(&mutex) < 0) {
    perror("pthread_mutex_lock");
    pthread_exit(NULL);
  }
  if (pthread_cond_timedwait(&cond, &mutex, &ts) < 0) {
    perror("pthread_cond_timedwait");
    pthread_exit(NULL);
  }

  if (pthread_cond_destroy(&cond) < 0) {
    perror("pthread_cond_destroy");
    pthread_exit(NULL);
  }
  if (pthread_mutex_destroy(&mutex) < 0) {
    perror("pthread_mutex_destroy");
    pthread_exit(NULL);
  }
}
void ipc1_cond(void *dummy) {
  if (pthread_mutex_lock(&Mutex) < 0) {
    perror("pthread_mutex_lock");
    pthread_exit(NULL);
  }
  if (pthread_cond_wait(&Sender, &Mutex) < 0) {
    perror("pthread_cond_wait");
    pthread_exit(NULL);
  }
  printf("ipc1 : Received request from ipc2...\n");
  int data = rand() % 100;
  //	data = 300;
  buffer = data;
  printf("ipc1 : Replied.\n");
  if (pthread_cond_signal(&Getter) < 0) {
    perror("pthread_cond_signal");
    pthread_exit(NULL);
  }
  if (pthread_mutex_unlock(&Mutex) < 0) {
    perror("pthread_mutex_unlock");
    pthread_exit(NULL);
  }
  ThreadUsleep(2 * 1000000);
  pthread_exit(NULL);
}

void ipc2_cond(void *dummy) {
  printf("ipc2 : Send a request...\n");
  if (pthread_mutex_lock(&Mutex) < 0) {
    perror("pthread_mutex_lock");
    pthread_exit(NULL);
  }
  if (pthread_cond_signal(&Sender) < 0) {
    perror("pthread_cond_wait");
    pthread_exit(NULL);
  }
  if (pthread_cond_wait(&Getter, &Mutex) < 0) {
    perror("pthread_cond_signal");
    pthread_exit(NULL);
  }
  int data = buffer;
  printf("ipc2 : This is a reply from ipc1. data : %d\n", data);
  if (pthread_mutex_unlock(&Mutex) < 0) {
    perror("pthread_mutex_unlock");
    pthread_exit(NULL);
  }

  pthread_exit(NULL);
}
void ipc1_sema(void *dummy) {
  if (sem_wait(&SSem) < 0) {
    perror("sem_post");
    pthread_exit(NULL);
  }
  if (sem_wait(&mutexSem) < 0) {
    perror("sem_wait");
    pthread_exit(NULL);
  }
  printf("ipc1 : Received request from ipc2...\n");
  int data = rand() % 100;
  //	data = 300;
  buffer = data;
  printf("ipc1 : Replied.\n");
  if (sem_post(&mutexSem) < 0) {
    perror("sem_post");
    pthread_exit(NULL);
  }
  if (sem_post(&GSem) < 0) {
    perror("sem_post");
    pthread_exit(NULL);
  }
  ThreadUsleep(2 * 1000000);
  pthread_exit(NULL);
}
void ipc2_sema(void *dummy) {
  printf("ipc2 : Send a request...\n");
  if (sem_post(&SSem) < 0) {
    perror("sem_post");
    pthread_exit(NULL);
  }
  if (sem_wait(&GSem) < 0) {
    perror("sem_wast");
    pthread_exit(NULL);
  }
  if (sem_wait(&mutexSem) < 0) {
    perror("sem_wait");
    pthread_exit(NULL);
  }
  int data = buffer;
  printf("ipc2 : This is a reply from ipc1. data : %d\n", data);
  if (sem_post(&mutexSem) < 0) {
    perror("sem_post");
    pthread_exit(NULL);
  }
  pthread_exit(NULL);
}
/*
mutex + condition var은 binary하게 작동한다.
이때 wait에서 기다리면 mutex를 반환하고 다시 시작할때 mutex를 가진다.
semaphore는 0, 1뿐만 아니라 prod-cons처럼 자연수로 카운팅 변수로 쓸 수 있음.

*/
int main() {
  pthread_t tid1, tid2;

  srand(0x9999);
  if (pthread_cond_init(&Sender, NULL) < 0) {
    perror("pthread_cond_init");
    pthread_exit(NULL);
  }
  if (pthread_cond_init(&Getter, NULL) < 0) {
    perror("pthread_cond_init");
    pthread_exit(NULL);
  }
  if (pthread_mutex_init(&Mutex, NULL) < 0) {
    perror("pthread_mutex_init");
    pthread_exit(NULL);
  }
  if (sem_init(&mutexSem, 0, 1) < 0) {
    perror("sem_init");
    exit(1);
  }
  if (sem_init(&GSem, 0, 0) < 0) {
    perror("sem_init");
    exit(1);
  }
  if (sem_init(&SSem, 0, 0) < 0) {
    perror("sem_init");
    exit(1);
  }
  // ipc using mutex and cond val.
  printf("ipc using mutex-cond\n");
  if (pthread_create(&tid1, NULL, (void *)ipc1_cond, (void *)NULL) < 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_create(&tid2, NULL, (void *)ipc2_cond, (void *)NULL) < 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_join(tid1, NULL) < 0) {
    perror("pthread_join");
    exit(1);
  }
  if (pthread_join(tid2, NULL) < 0) {
    perror("pthread_join");
    exit(1);
  }

  // ipc using semaphore
  printf("ipc using semaphore\n");
  if (pthread_create(&tid1, NULL, (void *)ipc1_sema, (void *)NULL) < 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_create(&tid2, NULL, (void *)ipc2_sema, (void *)NULL) < 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_join(tid1, NULL) < 0) {
    perror("pthread_join");
    exit(1);
  }
  if (pthread_join(tid2, NULL) < 0) {
    perror("pthread_join");
    exit(1);
  }
  if (pthread_cond_destroy(&Sender) < 0) {
    perror("sem_destroy");
  }
  if (pthread_cond_destroy(&Getter) < 0) {
    perror("sem_destroy");
  }
  if (pthread_mutex_destroy(&Mutex) < 0) {
    perror("pthread_mutex_destroy");
  }
  if (sem_destroy(&mutexSem) < 0) {
    perror("sem_destroy");
  }
  if (sem_destroy(&GSem) < 0) {
    perror("sem_destroy");
  }
  if (sem_destroy(&SSem) < 0) {
    perror("sem_destroy");
  }
}
