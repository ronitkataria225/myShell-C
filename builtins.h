#ifndef BUILTINS_H
#define BUILTINS_H 
#include "command.h"

int echo(struct command cmd);
int pwd(struct command cmd);
int cd(struct command cmd);
int builtin_exit(struct command cmd);
int builtin_complete(struct command cmd);
int type(struct command cmd, char* tempPath);

#endif