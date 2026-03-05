#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_shell
{
	char    **env;
	int     exit_status;
	int     running;
}   t_shell;

#endif