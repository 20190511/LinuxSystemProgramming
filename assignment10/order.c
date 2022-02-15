#include <stdio.h>
int main() {
  int a = 0x12345678;
  char *p = (char *)&a;

#if 0  // Little-Endian
	printf("Address %p: %#x\n", p, *p); p++;
	printf("Address %p: %#x\n", p, *p); p++;
	printf("Address %p: %#x\n", p, *p); p++;
	printf("Address %p: %#x\n", p, *p); p++;
#else  // *(p++)
  printf("Address %p: %#x\n", p, *p++);
  printf("Address %p: %#x\n", p, *p++);
  printf("Address %p: %#x\n", p, *p++);
  printf("Address %p: %#x\n", p, *p++);
#endif
}
