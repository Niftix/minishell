/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:28:31 by mville            #+#    #+#             */
/*   Updated: 2026/03/10 21:36:27 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_exec(t_shell *shell, int index)
{
	free(shell->env[index]);
	while (shell->env[index + 1])
	{
		shell->env[index] = shell->env[index + 1];
		index++;
	}
	shell->env[index] = NULL;
}

static void	unset_exec(t_shell *shell, char *name)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, name_len) == 0
			&& shell->env[i][name_len] == '=')
		{
			remove_exec(shell, i);
			return ;
		}
		i++;
	}
}

int	builtin_unset(t_shell *shell, t_ast *ast)
{
	int	i;

	i = 1;
	while (ast->args_cmd[i])
	{
		unset_exec(shell, ast->args_cmd[i]);
		i++;
	}
	return (0);
}
