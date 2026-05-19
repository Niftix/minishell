/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:28:31 by mville            #+#    #+#             */
/*   Updated: 2026/05/19 11:05:54 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_unset_id(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

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
			&& (shell->env[i][name_len] == '='
			|| shell->env[i][name_len] == '\0'))
		{
			remove_exec(shell, i);
			return ;
		}
		i++;
	}
}

int	blt_unset(t_shell *shell, t_ast *ast)
{
	int	i;

	i = 1;
	while (ast->args_cmd[i])
	{
		if (ast->args_cmd[i][0] == '-' && ast->args_cmd[i][1])
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(ast->args_cmd[i], 2);
			ft_putstr_fd(": invalid option\n", 2);
			return (2);
		}
		if (!is_valid_unset_id(ast->args_cmd[i]))
			return (unset_error(ast->args_cmd[i]));
		unset_exec(shell, ast->args_cmd[i]);
		i++;
	}
	return (0);
}
