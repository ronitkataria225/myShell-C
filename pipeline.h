#ifndef PIPE_H
#define PIPE_H
#include <stdbool.h>
#include "command.h"
struct pipeline
{
    struct command* commands;
    int pipeCount;
    bool isPipe;
};


#endif