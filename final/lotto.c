#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int count = 1;
int inputs = 0;
int lottos[6];
void signalHandler() {
  printf("\n%d\n", count);
  lottos[inputs] = count;
  inputs++;
  if (inputs == 6) {
    printf("Lotto number: ");
    for (int i = 0; i < 6; i++) printf("%d ", lottos[i]);
    printf("\n");
    exit(0);
  }
}

int main() {
  if (signal(SIGINT, signalHandler) == SIG_ERR) {
    perror("signal");
    exit(1);
  }
  while (1) {
    count = count % 45 + 1;
  }
}
