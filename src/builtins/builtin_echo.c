/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:12:23 by mville            #+#    #+#             */
/*   Updated: 2026/04/10 13:41:09 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

int	builtin_echo(t_ast *ast)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (ast->args_cmd[i] && check_n(ast->args_cmd[i]))
	{
		nl = 0;
		i++;
	}
	while (ast->args_cmd[i])
	{
		ft_putstr_fd(ast->args_cmd[i], 1);
		if (ast->args_cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", 1);
	return (0);
}
