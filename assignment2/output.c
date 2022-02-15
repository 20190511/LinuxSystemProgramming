#include <stdio.h>

int main() {
  char c = 'a', s[] = "hello";
  int i = 100;
  long l = 99999;
  float f = 3.14;
  double d = 99.999;
  int *p = &i;

  printf("Output: %c %s %d %#X %ld %.4f %.2lf %p\n", c, s, i, i, l, f, d, p);
  putchar(c);
  puts(s);
}
