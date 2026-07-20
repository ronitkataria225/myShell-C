#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL); // Flush after every printf
  char input[100];

  while (1) {
    printf("$ ");
    scanf("%s", input);
    printf("%s: command not found\n", input);
  }
  return 0;
}