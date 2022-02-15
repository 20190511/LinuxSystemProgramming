#include <stdio.h>
#include <unistd.h>

#include "record.h"

void print_record(Record *rp) {
  puts(rp->stud);
  puts(rp->num);
  puts(rp->dept);
}

int main(int argc, char *argv[]) {
  FILE *fp; // 파일 포인터
  Record rec;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s file\n", argv[0]);
    exit(1);
  }

  if ((fp = fopen(argv[1], "r+b")) == NULL) {
    perror("fopen");
    exit(1);
  }

  printf("-----Ordered Record List-----\n");
  // 레코드 크기 만큼 fp에서 하나 꺼내옴. 다 꺼내면 반복문 탈출.
  while (fread(&rec, sizeof(Record), 1, fp)) {
    print_record(&rec);
  }
  rewind(fp);
  getchar();  // 엔터 치면 넘어감.

  printf("-----Shuffled Record List (3, 6, 2, 4, 1, 5)-----\n");

  fseek(fp, sizeof(rec) * 2L, SEEK_SET);
  fread(&rec, sizeof(rec), 1, fp);
  print_record(&rec);

  fseek(fp, sizeof(rec) * 5L, SEEK_SET);
  fread(&rec, sizeof(rec), 1, fp);
  print_record(&rec);

  fseek(fp, sizeof(rec) * 1L, SEEK_SET);
  fread(&rec, sizeof(rec), 1, fp);
  print_record(&rec);

  fseek(fp, sizeof(rec) * 4L, SEEK_SET);  // 4번째로 포인터 조정.
  fread(&rec, sizeof(rec), 1, fp);
  print_record(&rec);

  fseek(fp, sizeof(rec) * 0L, SEEK_SET);
  fread(&rec, sizeof(rec), 1, fp);
  print_record(&rec);

  fseek(fp, sizeof(rec) * 4L, SEEK_SET);
  fread(&rec, sizeof(rec), 1, fp);
  print_record(&rec);
  getchar();

  printf("-----Updated Record List-----\n");

  fseek(fp, sizeof(rec) * 2L, SEEK_SET);
  fread(&rec, sizeof(rec), 1, fp);  // read를 해서 3번째 레코드로 이동하게됨
  strcpy(rec.dept, "Movie");              // 레코드 정보 수정.
  fseek(fp, sizeof(rec) * 2L, SEEK_SET);  // 다시 수정할 레코드로.
  fwrite(&rec, sizeof(rec), 1, fp);

  fseek(fp, sizeof(rec) * 5L, SEEK_SET);
  fread(&rec, sizeof(rec), 1, fp);
  strcpy(rec.dept, "Baseball");
  fseek(fp, sizeof(rec) * 5L, SEEK_SET);
  fwrite(&rec, sizeof(rec), 1, fp);

  rewind(fp);
  while (fread(&rec, sizeof(rec), 1, fp)) {
    print_record(&rec);
  }

  fclose(fp);
}
