#include "headers.h"
//echo hello > input.txt sfsfdf NULL
//0    1     2 3         4      5
//i = 2 is >
//j = 2
//replace > with sfsfdf
//j = 3
//replace input.txt with NULL
//argc 6 
//i = 2; j = 2; j+2 = 4; 4<=5; 2 <- 4; 
//tail -f /tmp/foo/file-1 | head -n 5 | somethings
int parser(struct command* cmd, struct pipeline* pipe){
    int j = 0;
    pipe->pipeCount = 0;
    pipe -> isPipe = false;
    for(int i = 0; i<cmd->argc; i++){
        // if(strcmp(cmd->args[i], "|") == 0){
        //     pipe->commands[pipe->pipeCount].args[j] = NULL;
        //     pipe->pipeCount++;
        //     pipe->isPipe = true;
        //     j = 0;
        // }
        // pipe->commands[pipe->pipeCount].args[j] = cmd->args[i];
        // j++; 
        
        if((strcmp(cmd->args[i], ">") == 0 || strcmp(cmd->args[i], "1>") == 0) && cmd->args[i+1] != NULL){
            cmd->redirectCode = 1;
            cmd->stdout_file = strdup(cmd->args[i+1]);
            for(int j = i; j+2 < cmd->argc; j++){
                cmd->args[j] = cmd->args[j+2];
            }
            cmd->argc -= 2;
            break;
        }
        if((strcmp(cmd->args[i], ">>") == 0 || strcmp(cmd->args[i], "1>>") == 0) && cmd->args[i+1] != NULL){
            cmd->redirectCode = 11;
            cmd->stdout_file = strdup(cmd->args[i+1]);
            for(int j = i; j+2 < cmd->argc; j++){
                cmd->args[j] = cmd->args[j+2];
            }
            cmd->argc -= 2;
            break;
        }

        if((strcmp(cmd->args[i], "2>") == 0) && cmd->args[i+1] != NULL){
            cmd->redirectCode = 2;
            cmd->stderr_file = strdup(cmd->args[i+1]);
            for(int j = i; j+2 < cmd->argc; j++){
                cmd->args[j] = cmd->args[j+2];
            }
            cmd->argc -= 2;
            break;
        }

        if((strcmp(cmd->args[i], "2>>") == 0) && cmd->args[i+1] != NULL){
            cmd->redirectCode = 22;
            cmd->stderr_file = strdup(cmd->args[i+1]);
            for(int j = i; j+2 < cmd->argc; j++){
                cmd->args[j] = cmd->args[j+2];
            }
            cmd->argc -= 2;
            break;
        }
    }
    return 1;
}