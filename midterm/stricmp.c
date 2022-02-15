#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int strcmp_p(char *dst, char *src) {
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
    if (tolower(*dst) != tolower(*src)) {
      int ret = tolower(*dst) - tolower(*src);
      return abs(ret) / ret;
    }
    dst++;
    src++;
  }
  int ret = *dst - *src;
  if (ret)
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
