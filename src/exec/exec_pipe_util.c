/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:59:01 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/05/20 18:59:04 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_no_cmd(t_ast *ast)
{
	if (ast->redirects && all_redirects(ast->redirects))
		return (1);
	return (0);
}

int	pipe_empty_cmd(t_ast *ast)
{
	if (ast->redirects && all_redirects(ast->redirects))
		return (1);
	ft_putstr_fd("minishell: : command not found\n", 2);
	return (127);
}

int	no_exec_path_checker(char **no_exec, char *tmp)
{
	if (*no_exec || access(tmp, F_OK) != 0 || check_if_directory(tmp))
		return (0);
	*no_exec = ft_strdup(tmp);
	if (!*no_exec)
		return (1);
	return (0);
}
