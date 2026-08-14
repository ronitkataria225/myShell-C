#include "headers.h"


const char* builtins[] = {
  "exit",
  "echo",
  "complete",
  "type", 
  "pwd",
  NULL
};

char *command_generator(const char *text, int state)
{
    static int index_builtin;
    static int index_exec;
    static int phase;
    static char** executablesList = NULL;
    if(executablesList == NULL){
      executablesList = makeExecutablesList();
    }

    if(state == 0){
      index_builtin = 0;
      index_exec = 0;
      phase = 0;
    }

    //printf("state=%d index=%d phase=%d\n", state, index_builtin, phase);
    if(phase == 0){
      while (builtins[index_builtin]) {
        const char *cmd = builtins[index_builtin++];
        if (strncmp(cmd, text, strlen(text)) == 0){
          return strdup(cmd);
        }
      }
      phase = 1;
    }
    
    //printf("state=%d index=%d phase=%d\n", state, index_exec, phase);
    while (executablesList[index_exec])
    {
      const char* exec = executablesList[index_exec++];
      if(strncmp(exec, text, strlen(text)) == 0){
        return strdup(exec);
      }
    }
    return NULL;
}

char **my_completion(const char *text, int start, int end)
{
    if (start == 0) {
        // Complete command names
        return rl_completion_matches(text, command_generator);
    }

    // For arguments, let Readline do its normal filename completion.
    return NULL;
}

int main(){
  char* input = NULL;
  size_t capacity = 0;
  struct command cmd;
  struct pipeline pipe;
  char *env_path = getenv("PATH");
  char tempPath[strlen(env_path)+1];
  char execPath[strlen(env_path) +1];
  int saved_stdout;
  int saved_stderr;
  int w_history;
  int r_history;
  using_history();
  HISTORY_STATE* myCurrentHistoryState = history_get_history_state();
  history_set_history_state(myCurrentHistoryState);
  if((r_history = read_history_range("history.txt", 0, 10)) != 0){
    perror("Isuue with r_history");
  }

  rl_attempted_completion_function = my_completion;
  
  while (1)
  {
    strcpy(tempPath, env_path);
    cmd.stdout_file = NULL;
    cmd.stderr_file = NULL;
    execPath[0] = '\0';
    //printf("$ ");
    //ssize_t len = getline(&input, &capacity, stdin);
    char* input = readline("$ ");
    add_history(input);
    if((w_history = write_history("history.txt")) != 0){
      perror("Issue with w_history");
    }
    
    ssize_t len = strlen(input);
    if(cmd.stderr_file != NULL){
      fprintf(stderr, "\n");
    }

    if(len > 0 && input[len - 1] == '\n'){
      input[len - 1] = '\0';
    }
    lexer(input, &cmd);
    // printf("Entering A\n");
    if(cmd.args[0] == NULL){
      continue;
    }
    // printf("Entering B\n");
    if(parser(&cmd, &pipe)){
      saved_stdout = dup(STDOUT_FILENO);
      saved_stderr = dup(STDERR_FILENO);
      redirect(cmd);
    }
    if(pipe.isPipe){

    }    

    if(bundle_builtins(cmd, tempPath)){
      restore_stderr(cmd, &saved_stderr);
      restore_stdout(cmd, &saved_stdout);
      continue;
    }

    if(bundle_executables(cmd, tempPath, execPath)){
      restore_stderr(cmd, &saved_stderr);
      restore_stdout(cmd, &saved_stdout);
      continue;
    }

    if(builtin_exit(cmd)){
      return 1;
    }
    
    restore_stderr(cmd, &saved_stderr);
    restore_stdout(cmd, &saved_stdout);
    printf("%s: command not found\n", input);
    continue;
  }
  // printf("Entering J\n");
  free(input);
  return 0;
}
