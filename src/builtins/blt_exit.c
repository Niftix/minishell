/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 18:23:37 by mville            #+#    #+#             */
/*   Updated: 2026/04/13 23:01:40 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_exit(t_shell *shell, t_ast *ast)
{
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 1);
	if (!ast->args_cmd[1])
		return (shell->run = 0, shell->status_exit);
	if (!ast->args_cmd[1][0] || !check_if_num_only(ast->args_cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(ast->args_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell->run = 0;
		return (2);
	}
	if (ast->args_cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	shell->run = 0;
	return ((unsigned char)ft_atoi(ast->args_cmd[1]));
}
