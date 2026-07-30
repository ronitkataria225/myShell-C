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

void lexer(char* input, struct command *cmd){
    int i = 0;
    int j = 0;
    int inSingle = 0;
    int inDouble = 0;
    char argBuffer[100];
    cmd->argc = 0;
    while (input[j] != '\0'){
        //echo   hello
        if(input[j] == '\\'){
            if(!inSingle && !inDouble){
                j++;
                argBuffer[i] = input[j];
                i++;
                j++;
                continue;
            }
            if(inDouble){
                if(input[j+1] == '\"' || input[j+1] == '\\' || input[j+1] == '$' || input[j+1] == '`'){
                    j++;
                    argBuffer[i] = input[j];
                    i++;
                    j++;
                    continue;
                }
            }
        }
        if(input[j] == ' '){
            if (!inSingle && !inDouble) {
                if (i > 0) {
                    argBuffer[i] = '\0';
                    cmd->args[cmd->argc] = strdup(argBuffer);
                    cmd->argc++;
                    i = 0;
                }
                j++;
                while (input[j] == ' '){
                    j++;
                    continue;
                }
            }
        }
        if(input[j] == '\''){
            if(!inDouble){ //not inside double quotes
                inSingle = !inSingle;
                j++;
                continue;
            }
            else{
                argBuffer[i] = input[j];
                i++;
                j++;
                continue;
            }
            //inside double finding a single : put and go on
        }

        if(input[j] == '\"'){
            if(!inSingle){
                inDouble = !inDouble;
                j++;
                continue;
            }
            else{
                argBuffer[i] = input[j];
                i++;
                j++;
                continue;
            }
        }
        argBuffer[i] = input[j];
        i++;
        j++; 
    }
    if(i>0){
        argBuffer[i] = '\0';
        cmd->args[cmd->argc] = strdup(argBuffer);
        cmd->argc++;
    }
    cmd->args[cmd->argc] = NULL;
    // for(int a = 0; a < cmd->argc; a++){
    //     printf("%s\n", cmd->args[a]);
    // }
}

    //echo 'asdsd''sdasds' 'sdasd'
    //arg 1 asdsdsdasds always
    //if you close a quote and it is followed by a quote without a space you take it as one argument
    //arg 2 sdasd
    //print arg 1 space arg 2