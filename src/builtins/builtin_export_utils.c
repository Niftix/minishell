/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:12:00 by mville            #+#    #+#             */
/*   Updated: 2026/04/10 15:12:00 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_opt(char *arg)
{
	return (arg && arg[0] == '-' && arg[1]);
}

int	find_var(t_shell *shell, char *arg, int mode)
{
	int		i;
	int		name_len;
	char	*equal;

	i = 0;
	equal = ft_strchr(arg, '=');
	if (!equal)
		name_len = ft_strlen(arg);
	else if (mode)
		name_len = equal - arg - 1;
	else
		name_len = equal - arg;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], arg, name_len) == 0
			&& (shell->env[i][name_len] == '='
			|| shell->env[i][name_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_line(char *s)
{
	int		i;
	char	*eq;

	eq = ft_strchr(s, '=');
	ft_putstr_fd("declare -x ", 1);
	if (!eq)
		return (ft_putstr_fd(s, 1), ft_putstr_fd("\n", 1));
	i = 0;
	while (&s[i] != eq + 1)
		write(1, &s[i++], 1);
	ft_putstr_fd("\"", 1);
	ft_putstr_fd(eq + 1, 1);
	ft_putstr_fd("\"\n", 1);
}

void	print_export(t_shell *shell)
{
	char	**env;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return ;
	i = 0;
	while (shell->env[i])
	{
		env[i] = shell->env[i];
		i++;
	}
	env[i] = NULL;
	sort_env(env);
	i = 0;
	while (env[i])
	{
		print_line(env[i]);
		i++;
	}
	free(env);
}
