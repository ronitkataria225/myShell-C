#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "command.h"
#include "lexer.h"
//#include "parser.h"
#include "builtins.h"
#include "executor.h"

int main(){
  char* input = NULL;
  size_t capacity = 0;
  struct command cmd;
  char *env_path = getenv("PATH");
  char tempPath[strlen(env_path)];
  while (1)
  {
    strcpy(tempPath, env_path);
    printf("$ ");
    ssize_t len = getline(&input, &capacity, stdin);

    if(len > 0 && input[len - 1] == '\n'){
      input[len - 1] = '\0';
    }
    lexer(input, &cmd);

    if(strcmp(cmd.args[0], "echo") == 0){
      if(echo(cmd) == 0){
        printf("\n");
        continue;
      }
    }
    if(strcmp(cmd.args[0], "pwd") == 0){
      if(pwd(cmd) == 0){
        continue;
      }
    }
    if(strcmp(cmd.args[0], "cd") == 0){
      if(cd(cmd) == 0){
        continue;
      }
    }
    if(strcmp(cmd.args[0], "type") == 0){
      if(type(cmd, tempPath) == 0){
        continue;
      }
    }
    if(strcmp(cmd.args[0], "exit") == 0){
      if(builtin_exit(cmd) == 0){
        return 0;
      }
    }
    printf("%s : command not found\n", input);
  }
  free(input);
  return 0;
}