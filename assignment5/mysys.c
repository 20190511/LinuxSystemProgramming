#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_BUF 1024

int mysystem(char *cmd) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {
    char *cmd_vec[MAX_BUF];
    char temp_token[MAX_BUF];
    // 마지막요소는 NULL이여야 한다.
    int currarg = 0;
    int argptr = 0;
    char *ptr = cmd;
    while (*ptr) {
      if (isspace(*ptr))  // whitespace 감지.
      {
        if (argptr) {
          temp_token[argptr] = '\0';
          // vector에 등록.
          cmd_vec[currarg] =
              (char *)calloc(strlen(temp_token) + 1, sizeof(char));
          strcpy(cmd_vec[currarg], temp_token);
          // temp 초기화.
          argptr = 0;
          currarg++;
        }
      } else  // 문자일때.
      {
        temp_token[argptr++] = *ptr;
      }
      ptr++;
    }
    if (argptr) {
      temp_token[argptr] = '\0';
      // vector에 등록.
      cmd_vec[currarg] = (char *)calloc(strlen(temp_token) + 1, sizeof(char));
      strcpy(cmd_vec[currarg], temp_token);
      argptr = 0;
      currarg++;
    }
    cmd_vec[currarg] = NULL;
    if (execvp(cmd_vec[0], cmd_vec) < 0) {
      perror(cmd_vec[0]);
      exit(1);
    }
    for (int fr = currarg - 1; fr >= 0; fr--) {
      free(cmd_vec[fr]);
    }
  }
  if (waitpid(pid, NULL, 0) < 0) {
    perror("waitpid");
    exit(1);
  }
  return 0;
}

int main(void) {
  mysystem("ps");
  mysystem("somecmdisnotcmd");
  // for error
  mysystem("ls -l");
  mysystem("date");
  mysystem("cp mysystem.c mysys.c");
}
