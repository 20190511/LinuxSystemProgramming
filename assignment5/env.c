#include <stdio.h>

int main(int argc, char *argv[],
         char *envp[])  // 메인 함수에 매개변수 뿐만 아니라 시스템 환경변수도 쓸
                        // 수 있음.
{
  int i;
  char **p;
  extern char **environ;  // 외부 환경변수를 모은 배열. > extern을 이용함.

  printf("List command-line arguments\n");
  for (i = 0; i < argc; i++) {
    printf("%s\n", argv[i]);
  }

  printf("\n");
  printf("List environment variables from environ variable\n");
#if 1  // 선택적으로 컴파일을 하게됨.
  for (i = 0; environ[i] != NULL; i++) {
    printf("%s\n", environ[i]);  // 마지막은 NULL.
  }
#else
  for (p = environ; *p != NULL; p++) {
    printf("%s\n", *p);
  }
#endif

  printf("\n");
  printf("List environment variables from envp variable\n");
#if 1
  for (i = 0; envp[i] != NULL; i++) {  // envp의 마지막은 NULL.
    printf("%s\n", envp[i]);
  }
#else
  for (p = envp; *p != NULL; p++) {
    printf("%s\n", *p);
  }
#endif
}
