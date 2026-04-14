/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:00:00 by mville            #+#    #+#             */
/*   Updated: 2026/04/14 17:25:22 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execve_fail_exit(t_shell *shell, t_ast *ast, char *path)
{
	if (check_if_directory(path))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ast->args_cmd[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(path);
		child_exit(shell, 126);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(ast->args_cmd[0], 2);
	ft_putstr_fd(": permission denied\n", 2);
	free(path);
	child_exit(shell, 126);
}

static void	path_null_exit(t_shell *shell, t_ast *ast)
{
	if (!ft_strchr(ast->args_cmd[0], '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ast->args_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		child_exit(shell, 127);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(ast->args_cmd[0], 2);
	if (check_if_directory(ast->args_cmd[0]))
		return (ft_putstr_fd(": Is a directory\n", 2),
			child_exit(shell, 126));
	if (access(ast->args_cmd[0], F_OK) == 0)
		return (ft_putstr_fd(": Permission denied\n", 2),
			child_exit(shell, 126));
	ft_putstr_fd(": No such file or directory\n", 2);
	child_exit(shell, 127);
}

void	exec_fork_child(t_shell *shell, t_ast *ast)
{
	char	*path;
	char	**exec_env;

	gest_signal();
	if (ast->redirects && all_redirects(ast->redirects))
		child_exit(shell, 1);
	path = resolve_cmd_path(shell, ast);
	if (!path)
		path_null_exit(shell, ast);
	exec_env = build_exec_env(shell);
	if (!exec_env)
	{
		free(path);
		child_exit(shell, 1);
	}
	execve(path, ast->args_cmd, exec_env);
	free(exec_env);
	execve_fail_exit(shell, ast, path);
}
