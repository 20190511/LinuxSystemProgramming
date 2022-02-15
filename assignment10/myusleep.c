#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

void myusleep(int secs, int usecs) {
  struct timeval tm;

  tm.tv_sec = secs;
  tm.tv_usec = usecs;

  if (select(0, NULL, NULL, NULL, &tm) < 0) {  // using select as pause/sleep.
    perror("select");
    return;
  }
}

int main() {
  printf("Sleep for 1.5 seconds.....\n");
  myusleep(1, 500000);
}
