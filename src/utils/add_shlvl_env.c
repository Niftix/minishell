/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shlvl_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:28:56 by mville            #+#    #+#             */
/*   Updated: 2026/04/29 16:37:18 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_shlvl_env(t_shell *shell, char *shlvl)
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
	new_env[i] = shlvl;
	if (!new_env[i])
		return (free(new_env), 1);
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

static int	update_shlvl_env(t_shell *shell, int i)
{
	int		vvalue;
	char	*value;
	char	*new_shlvl;

	vvalue = ft_atoi(shell->env[i] + 6);
	vvalue++;
	value = ft_itoa(vvalue);
	if (!value)
		return (1);
	new_shlvl = ft_strjoin("SHLVL=", value);
	free(value);
	if (!new_shlvl)
		return (1);
	free(shell->env[i]);
	shell->env[i] = new_shlvl;
	return (0);
}

int	check_if_shlvl_exist(t_shell *shell)
{
	char	*shlvl;
	int		i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
			return (update_shlvl_env(shell, i));
		i++;
	}
	shlvl = ft_strdup("SHLVL=1");
	if (!shlvl)
		return (1);
	i = add_shlvl_env(shell, shlvl);
	return (i);
}
