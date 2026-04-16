/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:36:14 by mville            #+#    #+#             */
/*   Updated: 2026/04/14 15:01:38 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_pwd_env(t_shell *shell, char *pwd)
{
	char	**new_env;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = pwd;
	if (!new_env[i])
		return (free(new_env), 1);
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

static int	check_if_pwd_exist(t_shell *shell)
{
	char	pwd[PATH_MAX];
	char	*real_pwd;
	int		i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
			return (0);
		i++;
	}
	if (!getcwd(pwd, PATH_MAX))
		return (0);
	real_pwd = ft_strjoin("PWD=", pwd);
	if (!real_pwd)
		return (1);
	i = add_pwd_env(shell, real_pwd);
	return (i);
}

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
	if (duplicate_env(shell, envp, count))
		return (1);
	if (check_if_pwd_exist(shell))
		return (ft_free_tab(shell->env), 1);
	return (0);
}
