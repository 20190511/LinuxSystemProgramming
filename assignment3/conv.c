#include <stdio.h>
#include <string.h>

#include "record.h"

int main(int argc, char *argv[]) {
  FILE *src, *dst;
  Record rec;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s source dest\n", argv[0]);
    exit(1);
  }

  if ((src = fopen(argv[1], "rt")) == NULL) {
    perror("fopen");
    exit(1);
  }
  if ((dst = fopen(argv[2], "wb")) == NULL) {
    perror("fopen");
    exit(1);
  }
  // fgets가 EOF에 갈때까지.
  while (fgets(rec.stud, SMAX, src)) {
    *strchr(rec.stud, '\n') = '\0';  // '\n'를 찾아 포인터 반환.
    fgets(rec.num, NMAX, src);
    *strchr(rec.num, '\n') = '\0';
    fgets(rec.dept, DMAX, src);
    *strchr(rec.dept, '\n') = '\0';
    // 한 라인당 받아서 레코드에 저장.

    fwrite(&rec, sizeof(Record), 1, dst);
    // fwrite를 이용해 dst에 레코드를 바이너리로 하나 저장.
  }

  fclose(src);
  fclose(dst);
}
