/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pwd_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:21:42 by mville            #+#    #+#             */
/*   Updated: 2026/04/29 16:25:27 by mville           ###   ########.fr       */
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

int	check_if_pwd_exist(t_shell *shell)
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
