/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 18:39:45 by mville            #+#    #+#             */
/*   Updated: 2026/04/07 13:53:39 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_id(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	exit_is_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	cd_chdir(char *dir)
{
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

char	*find_home(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "HOME=", 5) == 0)
			return (shell->env[i] + 5);
		i++;
	}
	return (NULL);
}

int	update_env(t_shell *shell, char *old_pwd, char *new_pwd)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("PWD=", new_pwd);
		}
		else if (ft_strncmp(shell->env[i], "OLDPWD=", 7) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("OLDPWD=", old_pwd);
		}
		i++;
	}
	return (0);
}
