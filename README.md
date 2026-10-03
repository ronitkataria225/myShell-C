# myShell-C
A custom shell made in C.

## General Workflow
- User Input(main.c)
- Make Tokens(lexer.c)
- Identify type of Token(parser.c)
- Exceute builtin commands **OR** external executables(bundles.c) 
- Restore STDOUT **AND** STDERR
- Exit Shell
- Clean input Buffer

## Detailed Workflow

### lexer.c
There are 3 primary states
1. Outside Quotes
2. Single Quotes
3. Double Quotes

All '\' outside quotes leads to ignoring the character just right to '\'. For example, '\$' would result in printing only the '$' character. (Ignore the single quotes in this example, it's not part of the output)

All '\' inside double quotes is put into effect for certain reserved characters such as $, ", ` .

Every space outside quotes results in a token. Every space inside quotes is ignored and becomes a part of the token.

Every closing (i.e even iteration) " OR ' for that string context leads to a token generation

Each token gets pushed onto the list of tokens in cmd's char* args list.

The list of tokens will end with a NULL token.

### parser.c

'>' OR '1>' token will redirect stdout to the file mentioned right after the token and will rewrite it

'>>' OR '1>>' token will redirect stdout to the file mentioned right after the token and will append it

'2>' token will redirect stdout to the file mentioned right after the token and will rewrite it

'2>>' token will redirect stdout to the file mentioned right after the token and will append it

### builtins.c

Estabilishes builtins commands:

- echo
- pwd: print present working directory
- cd: change directory
- ~: HOME directory
- exit: exit the shell
- type: print type of command, builtin/executable (with path)

### executor.c

Executables provided by Linux

Search all the directories of $PATH variable and whether the file is an executable

Store the file path

int redirect(struct command cmd) will set the stdout_file and stderr_file accordingly by checking the redirect code

## Other Features

### <TAB> Completions

The readline library uses a list of hard coded builtins and a list of all the executables obtained at every run of the program using the completion.c 

completion.c scans the files in $PATH and appends their name to a list if the file is an executable

### history

