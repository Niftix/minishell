/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 18:15:01 by mville            #+#    #+#             */
/*   Updated: 2026/04/13 23:01:19 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_env(t_shell *shell, t_ast *ast)
{
	int	i;

	if (ast->args_cmd[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(ast->args_cmd[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		return (127);
	}
	i = 0;
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
		{
			ft_putstr_fd(shell->env[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (0);
}
