#include "headers.h"

int findExecutable(char* command, char* tempPath, char* execPath){
    // printf("HI in exec\n");
    char candidate[1024];
    //strcpy(localPath, tempPath);
    char* dir;
    while((dir = strsep(&tempPath, ":")) != NULL){
        snprintf(candidate, sizeof(candidate), "%s/%s", dir, command);
        //printf("%s\n", candidate);
        if(access(candidate, X_OK) == 0){
            //printf("Exec yes\n");
            strcpy(execPath, candidate);
            return 1;
        }
    }
    return 0;
}

int redirect(struct command cmd){
    int fd_out = -1;
    // printf("Entered redirect : \n");
    if(cmd.stdout_file != NULL){
        // printf("Entered if: \n");
        if(cmd.redirectCode == 1){
            fd_out = open(cmd.stdout_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }

        if(cmd.redirectCode == 11){
            fd_out = open(cmd.stdout_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }

        if(fd_out > -1){
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
    }
    

    if(cmd.stderr_file != NULL){
        int fd_err = -1;
        if(cmd.redirectCode == 2){
            fd_err = open(cmd.stderr_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }

        if(cmd.redirectCode == 22){
            fd_err = open(cmd.stderr_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        if(fd_err > 0){
            dup2(fd_err, STDERR_FILENO);
            close(fd_err);
        }
        else{
            printf("something's wrong with stderr_file and cmd.redirectCode\n");
        }
    }
    return 0; 
}

void restore_stdout(struct command cmd, int* saved_stdout){
    if (cmd.stdout_file != NULL) {
        fflush(stdout);
        dup2(*saved_stdout, STDOUT_FILENO);
        close(*saved_stdout);
    }
}

void restore_stderr(struct command cmd, int* saved_stderr){
    if(cmd.stderr_file != NULL){
        fflush(stderr);
        dup2(*saved_stderr, STDERR_FILENO);
        close(*saved_stderr);
    }
}