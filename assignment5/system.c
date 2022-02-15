#include <stdio.h>
#include <stdlib.h>

int main() {
  int status;

  if ((status = system("date")) < 0) {  // date 커맨드 입력.
    perror("system");
    exit(1);
  }
  printf("exit status = %d\n", status);

  if ((status = system("nosuchcommand")) <
      0) {  // 없는 커맨드이면 -1 반환:에러.
    perror("system");
    exit(1);
  }
  printf("exit status = %d\n", status);
  if ((status = system("who; exit 44")) <
      0) {  // ; 세미콜론으로 여러 명령어입력 가능.
    perror("system");
    exit(1);
  }
  // system은 새로운 프로세스를 fork하기 때문에 exit은 그 프로세스를 벗어나는
  // 것. status는 0이 아니다.
  printf("exit status = %d\n", status);
}
