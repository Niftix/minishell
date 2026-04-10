/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:36:14 by mville            #+#    #+#             */
/*   Updated: 2026/03/05 17:56:26 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	duplicate_env(t_shell *shell, char **envp, int count)
{
	int	i;

	i = 0;
	while (i <= count)
	{
		shell->env[i] = NULL;
		i++;
	}
	i = 0;
	while (i < count)
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
			return (ft_free_tab(shell->env), 1);
		i++;
	}
	shell->env[i] = NULL;
	return (0);
}

int	shell_init(t_shell *shell, char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	shell->status_exit = 0;
	shell->run = 1;
	shell->in_pipe = 0;
	shell->stdin_backup = -1;
	shell->stdout_backup = -1;
	shell->last_pid = -1;
	shell->current_input = NULL;
	shell->t_current_lexer = NULL;
	shell->t_current_ast = NULL;
	shell->env = malloc(sizeof(char *) * (count + 1));
	if (!shell->env)
		return (1);
	return (duplicate_env(shell, envp, count));
}
