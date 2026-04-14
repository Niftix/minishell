/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core_blt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:58:03 by mville            #+#    #+#             */
/*   Updated: 2026/04/14 17:25:23 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_shell *shell, t_ast *ast)
{
	if (ft_strcmp(ast->args_cmd[0], "cd") == 0)
		return (blt_cd(shell, ast));
	if (ft_strcmp(ast->args_cmd[0], "unset") == 0)
		return (blt_unset(shell, ast));
	if (ft_strcmp(ast->args_cmd[0], "pwd") == 0)
		return (blt_pwd());
	if (ft_strcmp(ast->args_cmd[0], "exit") == 0)
		return (blt_exit(shell, ast));
	if (ft_strcmp(ast->args_cmd[0], "echo") == 0)
		return (blt_echo(shell, ast));
	if (ft_strcmp(ast->args_cmd[0], "env") == 0)
		return (blt_env(shell, ast));
	if (ft_strcmp(ast->args_cmd[0], "export") == 0)
		return (blt_export(shell, ast));
	return (1);
}
