/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 18:23:37 by mville            #+#    #+#             */
/*   Updated: 2026/04/16 21:03:54 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_num_only(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	blt_exit(t_shell *shell, t_ast *ast)
{
	int	status;

	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 1);
	if (!ast->args_cmd[1])
		return (shell->run = 0, shell->status_exit);
	if (!ast->args_cmd[1][0] || !check_if_num_only(ast->args_cmd[1]))
		return (shell->run = 0, blt_exit_num_error(ast->args_cmd[1]));
	if (ast->args_cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	status = blt_exit_parse_status(ast->args_cmd[1]);
	if (status == 256)
		return (shell->run = 0, blt_exit_num_error(ast->args_cmd[1]));
	shell->run = 0;
	return (status);
}
