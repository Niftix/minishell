/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:36:14 by mville            #+#    #+#             */
/*   Updated: 2026/03/05 16:58:13 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	duplicate_env(t_shell *shell, char **envp, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (envp[i][j])
			j++;
		shell->env[i] = malloc(sizeof(char) * (j + 1));
		if (!shell->env[i])
			return (ft_free(shell->env), 1);
		ft_strcpy(shell->env[i], envp[i]);
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
	shell->env = malloc(sizeof(char *) * (count + 1));
	if (!shell->env)
		return (1);
	return (duplicate_env(shell, envp, count));
}
