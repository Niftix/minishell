/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:00:00 by mville            #+#    #+#             */
/*   Updated: 2026/04/14 17:25:21 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_exec_env(char **env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			count++;
		i++;
	}
	return (count);
}

char	**build_exec_env(t_shell *shell)
{
	char	**env;
	int		i;
	int		j;

	env = malloc(sizeof(char *) * (count_exec_env(shell->env) + 1));
	if (!env)
		return (NULL);
	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			env[j++] = shell->env[i];
		i++;
	}
	env[j] = NULL;
	return (env);
}
