#ifndef EXECUTOR_H
#define EXECUTOR_H 

int findExecutable(char* command, char* tempPath, char* execPath);
int redirect(struct command cmd);
void restore_stdout(struct command cmd, int *saved_stdout);
void restore_stderr(struct command cmd, int* saved_stderr);

#endif