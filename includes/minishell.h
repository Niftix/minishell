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
	int     status_exit;
	int     run;
}   t_shell;

void shell_init(t_shell *shell, char **envp);

#endif