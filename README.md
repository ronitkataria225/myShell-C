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

Every closing(i.e even iteration) " OR ' for that string context leads to a token generation

Each token gets pushed onto the list of tokens in cmd's args list.

The list of tokens will end with a NULL token.

