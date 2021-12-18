#include "ext/io.h"
#include<stdio.h>
#include<string.h>

int main() {
  char *line = NULL;
  cgetline(&line, 0, stdin);
  //printf("%s", line);
  // Nhap: 1 2.5 3 + -
  /* Xuat:
    1
    2.5
    3
    +
    -
  */
  if (line[strlen(line) - 1] == '\n') {
    line[strlen(line) - 1] = '\0';
  }
  char *tok = strtok(line, " ");
  while (tok) {
    printf("%s\n", tok);
    tok = strtok(NULL, " ");
  }
  free(line);
  return 0;
}