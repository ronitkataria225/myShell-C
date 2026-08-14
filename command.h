#ifndef COMMAND_H
#define COMMAND_H

struct command {
    char *args[50];
    int argc;
    char* stdout_file;
    char* stderr_file;
    int redirectCode;
};

#endif