/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_blt_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 01:52:21 by mville            #+#    #+#             */
/*   Updated: 2026/04/13 22:59:49 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	display_export(char *arg)
{
	char	*equal_sign;
	int		i;

	equal_sign = ft_strchr(arg, '=');
	ft_putstr_fd("declare -x ", 1);
	if (equal_sign == NULL)
	{
		ft_putstr_fd(arg, 1);
		ft_putstr_fd("\n", 1);
		return ;
	}
	write(1, arg, (equal_sign - arg) + 1);
	ft_putstr_fd("\"", 1);
	i = 1;
	while (equal_sign[i])
	{
		if (equal_sign[i] == '"' || equal_sign[i] == '\\'
			|| equal_sign[i] == '$' || equal_sign[i] == '`')
			ft_putstr_fd("\\", 1);
		write(1, &equal_sign[i], 1);
		i++;
	}
	ft_putstr_fd("\"\n", 1);
}

void	no_arg_print_export(t_shell *shell)
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
		display_export(env[i]);
		i++;
	}
	free(env);
}

int	check_format_is_valid(char *s)
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
