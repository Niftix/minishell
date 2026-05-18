/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:05:01 by mville            #+#    #+#             */
/*   Updated: 2026/05/17 14:06:00 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_path_env(t_shell *shell, char *path)
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
	new_env[i] = path;
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

int	check_if_path_exist(t_shell *shell)
{
	char	*path;
	int		i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
			return (0);
		i++;
	}
	path = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:"
			"/usr/sbin:/usr/bin:/sbin:/bin");
	if (!path)
		return (1);
	return (add_path_env(shell, path));
}
