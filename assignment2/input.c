#include <stdio.h>

int main() {
  char c, s[80];
  int i;
  long l;
  float f;
  double d;

  scanf("%c %s %d %ld %f %lf", &c, s, &i, &l, &f, &d);
  // 4.2lf , %-4d등으로 여백 및 소수점 조정가능.
  printf("Output: %c %s %d %ld %.4f %.2lf\n", c, s, i, l, f, d);

  c = getchar();
  putchar(c);

  gets(s);
  puts(s);
}
