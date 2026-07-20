#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);// Flush after every printf
  char input[100];
  char exit[] = "exit";
  char echo[] = "echo ";
  char *env_path = getenv("PATH");
  char *myPath;
  int builtIn = 0;
  int typeFound = 0;
  int exists = 0;
  char tempPath[4096];
  char typeCandidate[1000];

  if (!env_path) {
    return 1;
  }

  char path[4096];

  snprintf(path, sizeof(path), "%s", env_path);

  while (1) {
    strcpy(tempPath, path);
    printf("$ ");
    fgets(input, sizeof(input), stdin);
    input[strlen(input) - 1] = '\0'; // fets() also counts the enter('\n') input when done with a line, so it also prints the newline when writing the input onto the screen
    if (strcmp(input, exit) == 0) {
      return 0;
    }

    // Better coding practice
    else if (strncmp(input, echo, 5) == 0) {
      printf("%s\n", input + 5);
    }

    else if (strncmp(input, "type ", 5) == 0) {
      typeFound = 0;

      if (strcmp(input + 5, "exit") == 0 || strcmp(input + 5, "echo") == 0 ||
          strcmp(input + 5, "type") == 0) {
        printf("%s is a shell builtin\n", input + 5);
        typeFound = 1;
      }

      // LOOP: read till you get a / for a file and till : for a new path
      // outer loop :

      if (typeFound == 0) {
        myPath = strtok(tempPath, ":");
        while (myPath != NULL) {
          strcpy(typeCandidate, myPath);
          strcat(typeCandidate, "/");
          strcat(typeCandidate, input + 5);
          // printf("Checking: %s\n", typeCandidate);
          if (access(typeCandidate, X_OK) == 0) {
            typeFound = 1;
            printf("%s is %s\n", input + 5, typeCandidate);
            break;
          }
          myPath = strtok(NULL, ":");
        }
      }

      if (typeFound == 0) {
        printf("%s: not found\n", input + 5);
      }
    }

    else {
      printf("%s: command not found\n", input);
    }
  }
  return 0;
}
