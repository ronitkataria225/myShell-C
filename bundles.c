#include "headers.h"

int bundle_builtins(struct command cmd, char* tempPath){
    if(echo(cmd)){
      printf("\n");
      return 1;
    }
    // printf("Entering D\n");
    if(pwd(cmd)){
        return 1;
    }
    // printf("Entering E\n");
    if(cd(cmd)){
      return 1;
    }
    if(type(cmd, tempPath)){
    //   restore_stderr(cmd, &saved_stderr);
    //   restore_stdout(cmd, &saved_stdout);
    //   continue;
    }
    // printf("Entering G\n");
}

int bundle_executables(struct command cmd, char* tempPath,char* execPath){
    if(findExecutable(cmd.args[0], tempPath, execPath)){
      cmd.args[cmd.argc] = NULL;
      // printf("Entered executable\n");
      pid_t pid = fork();
      if(pid<0){
        perror("Fork Failed:");
        return 1;
      }

      else if(pid == 0){
        if(execv(execPath, cmd.args)== -1){
          perror("Execution Failed");
        }
        exit(EXIT_FAILURE);
      }
      else{
        int status;
        waitpid(pid, &status, 0);
        return 1;
      }
    }
}