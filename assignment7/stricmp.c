#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int strcmp_p(char *dst, char *src) {  // 대소문자 구분하는 strcmp_p
  while ((*dst) == (*src) && (*dst)) {
    dst++, src++;
  }
  if (*dst > *src)
    return 1;
  else if (*dst < *src)
    return -1;
  else
    return 0;
}

int stricmp_p(char *dst, char *src) {
  while (*dst && *src) {
    if (tolower(*dst) != tolower(*src))  // tolower로 소문자화
    {
      int ret = tolower(*dst) - tolower(*src);
      return abs(ret) / ret;
    }
    dst++;
    src++;
  }
  int ret = *dst - *src;  // 차이 만큼 반환.
  // 음수이면 dst가 앞선것.
  if (ret)  // -1 또는 1 로 변환.
    return abs(ret) / ret;
  else  // div by zero.
    return ret;
}

int main() {
  char str1[] = "Hello";
  char str2[] = "hello";
  char str3[] = "World!";
  printf("%d : %d\n", stricmp_p(str1, str2), stricmp_p(str1, str3));
}
