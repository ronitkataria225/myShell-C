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

int findExecutable(char* command, char* tempPath, char* execPath){
    char candidate[1024];
    //strcpy(localPath, tempPath);
    char* dir;
    while((dir = strsep(&tempPath, ":")) != NULL){
        snprintf(candidate, sizeof(candidate), "%s/%s", dir, command);
        if(access(candidate, X_OK) == 0){
            //printf("Exec yes\n");
            strcpy(execPath, candidate);
            return 1;
        }
    }
    return 0;
}