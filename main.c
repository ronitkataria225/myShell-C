#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);// Flush after every printf
  char input[100];
  char exit[] = "exit";
  char echo[] = "echo ";
  while (1) {
    printf("$ ");
    fgets(input, sizeof(input), stdin);
    input[strlen(input) - 1] = '\0'; // fets() also counts the enter('\n') input when done with a line, so it also prints the newline when writing the input onto the screen
    if (strcmp(input, exit) == 0) {
      return 0;
    }

    // else if(input[0] == 'e' && input[1] == 'c' && input[2] == 'h' && input[3]
    // == 'o' && input[4] == ' '){
    //   for(int i=5; i<strlen(input); i++){
    //     printf("%c", input[i]);
    //   }
    //   printf("\n");
    //   continue;
    // } OUR APPROACH

    // Better coding practice
    else if (strncmp(input, echo, 5) == 0) {
      printf("%s\n", input + 5);
    }

    else if (strncmp(input, "type ", 5) == 0) {

      if (strcmp(input + 5, "exit") == 0 || strcmp(input + 5, "echo") == 0 ||
          strcmp(input + 5, "type") == 0) {
        printf("%s is a shell builtin\n", input + 5);
      }

      else {
        printf("%s: not found\n", input + 5);
      }
    }

    else {
      printf("%s: command not found\n", input);
    }
  }
  return 0;
}
