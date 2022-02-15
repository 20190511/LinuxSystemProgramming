#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void adding(int *start)  // 더하는 함수. start에 결과값 반환.
{
  int ret = 0;
  for (int i = 0; i < 50; i++) ret += *start + i;
  *start = ret;
  pthread_exit(NULL);
}

int main(void) {
  pthread_t tid1, tid2;
  int left = 1, right = 51;
  if (pthread_create(&tid1, NULL, (void *)adding, (void *)&left) <
      0) {  // 쓰레드 생성.
    perror("pthread_create");
    exit(1);
  }
  if (pthread_create(&tid2, NULL, (void *)adding, (void *)&right) < 0) {
    perror("pthread_create");
    exit(1);
  }
  if (pthread_join(tid1, NULL))  // tid1 먼저.
  {                              // tid1이 끝날때 까지 기다림.
    perror("pthread_join");
    exit(1);
  }
  if (pthread_join(tid2, NULL)) {
    perror("pthread_join");
    exit(1);
  }
  printf("%d\n", left + right);  // 반환값.
}
