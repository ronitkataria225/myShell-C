#ifndef HEADERS_H
#define HEADERS_H

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "pipeline.h"
#include "command.h"
#include "lexer.h"
#include "parser.h"
#include "builtins.h"
#include "executor.h"
#include "completions.h"
#include "bundles.h"

#endif