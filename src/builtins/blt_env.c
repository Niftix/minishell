/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 18:15:01 by mville            #+#    #+#             */
/*   Updated: 2026/05/19 19:05:31 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_env(t_shell *shell, t_ast *ast)
{
	int	i;

	if (ast->args_cmd[1])
		return (ft_putstr_fd("minishell: env: too many arguments\n", 2), 127);
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
