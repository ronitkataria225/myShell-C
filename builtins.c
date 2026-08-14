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

int echo(struct command cmd){
  if(strcmp(cmd.args[0], "echo") == 0){
    for(int i=1; i<cmd.argc; i++){
      printf("%s", cmd.args[i]);
      if(i != cmd.argc - 1){
        printf(" ");
      }
    }
    return 1;
  }
  return 0;
} 

int pwd(struct command cmd){
  if(strcmp(cmd.args[0], "pwd") == 0){
    char cwd[100];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
          perror("pwd");
          return 0;
    }
    //getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    return 1;
  }
  return 0;
}

int cd(struct command cmd){
  if(strcmp(cmd.args[0], "cd") == 0){
    if(cmd.argc > 2){
      printf("cd: too many arguments\n");
      return 1;
    }
    char *home = getenv("HOME");
    if (strcmp(cmd.args[1], "~") == 0) {
      chdir(home);
      return 1;
    }
    if (chdir(cmd.args[1]) != 0) {
      fprintf(stderr, "cd: %s: %s\n", (cmd.args[1]), strerror(errno));
    }
    return 1;
  }
  return 0;
}

int builtin_exit(struct command cmd){
  if(strcmp(cmd.args[0], "exit") == 0){
      return 1;
  }
  return 0;
}

// int builtin_complete(struct command cmd){
//   if(strcmp(cmd.args[0], "complete") == 0){
//     return 1;
//   }
//   return 0;
// }


int type(struct command cmd, char* tempPath){
  if(strcmp(cmd.args[0], "type") == 0){
    char* localPath[strlen(tempPath)+1];
    char execPath[strlen(tempPath)+1];
    for(int i=1; i<cmd.argc; i++){
      strcpy(execPath, tempPath);
      execPath[0] = '\0';
      if(strcmp(cmd.args[i], "type") == 0 || strcmp(cmd.args[i], "cd") == 0 || strcmp(cmd.args[i], "pwd") == 0 || strcmp(cmd.args[i], "exit") == 0 || strcmp(cmd.args[i], "echo") == 0 || strcmp(cmd.args[i], "complete") == 0){
        printf("%s is a shell builtin\n", cmd.args[1]);
      }
      else if(findExecutable(cmd.args[i], tempPath, execPath) == 1){
        printf("%s is %s\n", cmd.args[i], execPath);
      }
      else{
        printf("%s: not found\n", cmd.args[1]);
      }
    }
    return 1;
  }
  return 0;
}
