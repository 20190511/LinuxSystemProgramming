#include <stdio.h>

int strlen_p(char *str) {
  int len = 0;

  // char 포인터가 널일때 종료한다. 널이면 끝이므로
  // 널을 만날때까지 increment한 값이 길이다.
  while (*(str++)) {
    len++;
  }
  return len;
}

int strlen_a(char str[]) {
  int i;
  // 위의 포인터를 이용한 함수와 기능적으로 동일하다.
  for (i = 0; str[i] != '\0'; i++)
    ;
  return i;
}

void strcpy_p(char *dst, char *src) {
  // src에서 dst로 복사를 하는 함수이다.
  // 따라서 src의 시작부터 끝(종료 조건 : NULL)까지
  // 두 포인터 모두 increment하면서 dst에 값을 대입힌다.

  while (*src) {
    *(dst++) = *(src++);
  }
  // 반복문이 끝나면 *src = NULL이다.
  // 따라서 dst도 동일하게 NULL을 대입하여 끝을 알 수 있게한다.
  *dst = *src;
}

void strcpy_a(char dst[], char src[]) {
  int i;

  // 위의 포인터를 이용한 함수와 기능적으로 동일하다.
  for (i = 0; src[i] != '\0'; i++) dst[i] = src[i];
  dst[i] = src[i];
}

void strcat_p(char *dst, char *src) {
  // dst뒤에 src를 붙이는 함수이다.
  while (*dst++)
    ;
  // dst의 끝(NULL)다음까지 이동해서 dst--한다.
  dst--;
  *dst = *src;
  // dst의 널을 src의 첫번째 원소로 바꾼다.
  while (*src) {
    *(dst++) = *(src++);
  }
  // 반복문을 통해 값을 대입하고 NULL까지 대입한다.
  *dst = *src;
}

void strcat_a(char dst[], char src[]) {
  int i, j;

  // 위의 포인터를 이용한 함수와 기능적으로 동일하다.
  for (i = 0; dst[i] != '\0'; i++)
    ;
  for (j = 0; src[j] != '\0'; j++) dst[i + j] = src[j];
  dst[i + j] = '\0';
}

int strcmp_p(char *dst, char *src) {
  while ((*dst) == (*src) && (*dst)) {
    // dst와 src의 문자열의 문자가 다를때까지
    // 동일할 수 있으므로 dst가 NULL이어도 종료.
    dst++, src++;
  }
  // 아스키 코드의 앞서는 순으로 비교하여 -1,0,1중 하나로 반환한다.
  if (*dst > *src)
    return 1;
  else if (*dst < *src)
    return -1;
  else
    return 0;
}

int strcmp_a(char dst[], char src[]) {
  int i;
  for (i = 0; dst[i] == src[i]; i++)
    if (!dst[i])
      //	NULL이면 나가기.
      break;
  if (dst[i] > src[i])
    return 1;
  else if (dst[i] < src[i])
    return -1;
  else
    return 0;
}

int main() {
  int len1, len2;
  char str1[20], str2[20];

  len1 = strlen_p("Hello");
  len2 = strlen_a("Hello");
  printf("strlen: p=%d, a=%d\n", len1, len2);

  strcpy_p(str1, "Hello");
  strcpy_a(str2, "Hello");
  printf("strcpy: p=%s, a=%s\n", str1, str2);

  strcat_p(str1, ", World!");
  strcat_a(str2, ", World!");
  printf("strcat: p=%s, a=%s\n", str1, str2);

  printf("strcmp(\"Hello\" <> \"Hello\") p = %d\n", strcmp_p("Hello", "Hello"));
  // 동일하므로 0
  printf("strcmp(\"Hello\" <> \"Hello\") a = %d\n", strcmp_a("Hello", "Hello"));
  // 동일하므로 0
  printf("strcmp(\"abcde\" <> \"abcd\") p = %d\n", strcmp_p("abcde", "abcd"));
  // e 와 NULL을 비교하므로 1을 반환
  printf("strcmp(\"acde\" <> \"acdf\") a = %d\n", strcmp_a("acde", "acdf"));
  // e 와 f을 비교하므로 -1을 반환
  printf("strcmp(\"AAAA\" <> \"aaaa\") p = %d\n", strcmp_p("AAAA", "aaaa"));
  // 아스키 코드를 통해 비교하므로 사전순은 아니다.
  printf("strcmp(\"aaBB\" <> \"BBaa\") a = %d\n", strcmp_a("aaBB", "BBaa"));
  // 대소문자 아스키코드 차이로 인해 1이 반환됨.
}
