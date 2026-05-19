*This project has been created as part of the 42 curriculum by mville, vcucuiet.*

# Minishell

## Description

Minishell is a project that consists of recreating a simple shell inspired by Bash.

The main goal is to understand how a shell operates under the hood:
- Reading a command line
- Tokenizing the input (Lexer)
- Parsing the tokens
- Building an Abstract Syntax Tree (AST)
- Executing the commands
- Managing pipes, redirections, environment variables, heredocs, and builtins

This project primarily allowed us to dive deep into process creation, file descriptors, signal handling, and the overall behavior of a Unix shell.

## Instructions

### Compilation

Compile the project using the provided Makefile:

`make`

### Execution

Run the shell with:

`./minishell`

### Cleaning

To clean the generated object files and the executable, you can use:

`make clean`

`make fclean`

`make re`

## Features

This project successfully handles the following features:
- Simple command execution
- Builtins: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, and `exit`
- Pipes: `|`
- Redirections: `<`, `>`, `>>`, and `<<` (heredocs)
- Environment variables expansion (e.g. `$USER`)
- Exit status variable: `$?`
- Wildcards: `*` (Bonus)
- Logical operators and priorities using an AST: `&&`, `||`, and `()` (Bonus)
- Signal handling in interactive mode (`ctrl-C`, `ctrl-D`, `ctrl-\`)

## Resources

- https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b
- https://medium.com/@gibrat.dylan/minishell-42-lart-de-cr%C3%A9er-un-shell-performant-et-maintenable-53c0aede140e
- https://buzut.net/cours/versioning-avec-git/bien-nommer-ses-commits
- https://devdocs.io/c/
- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
- https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html
- https://tldp.org/LDP/abs/html/internal.html
- https://www.oilshell.org/blog/2019/02/07.html#parsing
- https://www.oilshell.org/blog/2017/02/11.html
- https://trove.assistants.epita.fr/docs/42sh/guide/prerequisites/

## AI Usage

AI tools were used as a tutor to better understand the most abstract parts of the project, especially the transition from the lexer to the parser, and finally to the AST.

Initially, building an AST seemed highly complex. The AI helped clarify the theory behind this data structure and explained why it was a robust and necessary solution for managing operator priorities.

It was also used to better understand the exact role of specific C functions and the internal behavior of Bash. Overall, AI served mainly to explain, simplify complex concepts, and unblock our understanding.

## Notes

This project strictly follows the 42 School Minishell subject guidelines. The goal is not to entirely recreate Bash, but to accurately reproduce its core mechanisms within the required constraints.
