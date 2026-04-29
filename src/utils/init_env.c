/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:36:14 by mville            #+#    #+#             */
/*   Updated: 2026/04/29 17:38:11 by mville           ###   ########.fr       */
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

static void	init_shell_value(t_shell *shell)
{
	shell->status_exit = 0;
	shell->run = 1;
	shell->in_pipe = 0;
	shell->stdin_backup = -1;
	shell->stdout_backup = -1;
	shell->last_pid = -1;
	shell->current_input = NULL;
	shell->input_stash.stash = NULL;
	shell->input_stash.idx = 0;
	shell->t_current_lexer = NULL;
	shell->t_current_ast = NULL;
}

int	shell_init(t_shell *shell, char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	init_shell_value(shell);
	shell->env = malloc(sizeof(char *) * (count + 1));
	if (!shell->env)
		return (1);
	if (duplicate_env(shell, envp, count))
		return (1);
	if (check_if_shlvl_exist(shell))
		return (ft_free_tab(shell->env), 1);
	if (check_if_pwd_exist(shell))
		return (ft_free_tab(shell->env), 1);
	return (0);
}
