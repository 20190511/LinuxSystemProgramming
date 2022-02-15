#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
// #include "synclib.h"
#define NLOOPS 5  // 5번 루프

sem_t waitChild, waitParent, mutexSem;

void parentRoutine(void *voidp) {
  for (int i = 0; i < NLOOPS; i++) {
    if (sem_wait(&waitChild)) {
      perror("sem_wait");
      pthread_exit(NULL);
    }
    if (sem_wait(&mutexSem)) {
      perror("sem_wait");
      pthread_exit(NULL);
    }
    printf("Parent : Tell to child\n");
    printf("Parent : Wait for child to tell\n");
    if (sem_post(&mutexSem)) {
      perror("sem_post");
      pthread_exit(NULL);
    }
    if (sem_post(&waitParent)) {
      perror("sem_post");
      pthread_exit(NULL);
    }
  }

  pthread_exit(NULL);
}

void childRoutine(void *voidp) {
  for (int i = 0; i < NLOOPS; i++) {
    printf("Child : Wait for parent to tell\n");
    if (sem_wait(&waitParent)) {
      perror("sem_wait");
      pthread_exit(NULL);
    }
    if (sem_wait(&mutexSem)) {
      perror("sem_wait");
      pthread_exit(NULL);
    }
    printf("Child : Tell to parent\n");
    if (sem_post(&mutexSem)) {
      perror("sem_post");
      pthread_exit(NULL);
    }
    if (sem_post(&waitChild)) {
      perror("sem_post");
      pthread_exit(NULL);
    }
  }

  pthread_exit(NULL);
}

int main() {
  int i;
  pthread_t parentID, childID;

  if (sem_init(&waitChild, 0, 1) < 0) {
    perror("sem_init");
    exit(1);
  }
  if (sem_init(&waitParent, 0, 0) < 0) {
    perror("sem_init");
    exit(1);
  }
  if (sem_init(&mutexSem, 0, 1) < 0) {
    perror("sem_init");
    exit(1);
  }
  if (pthread_create(&parentID, NULL, (void *)parentRoutine, NULL)) {
    perror("pthread_create");
    exit(1);
  }
  if (pthread_create(&childID, NULL, (void *)childRoutine, NULL)) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_join(parentID, NULL)) {
    perror("pthread_join");
    exit(1);
  }
  if (pthread_join(childID, NULL)) {
    perror("pthread_join");
    exit(1);
  }
  if (sem_destroy(&waitParent)) {  // semaphore destroy
    perror("sem_destroy");
  }
  if (sem_destroy(&waitChild)) {
    perror("sem_destroy");
  }
  if (sem_destroy(&mutexSem)) {
    perror("sem_destroy");
  }
}
