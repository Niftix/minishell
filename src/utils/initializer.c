#include "minishell.h"

void shell_init(t_shell *shell, char **envp)
{
 shell->env = &envp;
 shell->status_exit = 0;
 shell->run = 1;
}