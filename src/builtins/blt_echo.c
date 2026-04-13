/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:12:23 by mville            #+#    #+#             */
/*   Updated: 2026/04/13 23:47:05 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	blt_echo(t_shell *shell, t_ast *ast)
{
	int	i;
	int	n_flag;

	(void)shell;
	i = 1;
	n_flag = 0;
	while (ast->args_cmd[i] && check_n_flag(ast->args_cmd[i]))
	{
		n_flag = 1;
		i++;
	}
	while (ast->args_cmd[i])
	{
		ft_putstr_fd(ast->args_cmd[i], 1);
		if (ast->args_cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}
