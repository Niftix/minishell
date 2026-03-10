/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:16:54 by mville            #+#    #+#             */
/*   Updated: 2026/03/10 21:43:05 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execve_fail_exit(t_ast *ast, char *path)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(ast->args_cmd[0], 2);
	ft_putstr_fd(": permission denied\n", 2);
	free(path);
	exit(126);
}

static void	path_null_exit(t_ast *ast)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(ast->args_cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

static void	exec_fork_child(t_shell *shell, t_ast *ast)
{
	char	*path;

	gest_signal();
	if (ast->redirects && all_redirects(ast->redirects))
		exit(1);
	path = find_cmd_path(shell, ast);
	if (!path)
		path_null_exit(ast);
	execve(path, ast->args_cmd, shell->env);
	execve_fail_exit(ast, path);
}

static int	exec_builtin_with_redirect(t_shell *shell, t_ast *ast)
{
	int	status;

	if (fd_save(shell))
		return (1);
	if (all_redirects(ast->redirects))
	{
		fd_recovery(shell);
		return (1);
	}
	status = exec_builtins(shell, ast);
	fd_recovery(shell);
	return (status);
}

int	exec_cmd(t_shell *shell, t_ast *ast)
{
	int		status;
	pid_t	pid;

	if (!ast->args_cmd || !ast->args_cmd[0])
		return (0);
	if (check_builtins(ast->args_cmd[0]))
	{
		if (ast->redirects)
			status = exec_builtin_with_redirect(shell, ast);
		else
			status = exec_builtins(shell, ast);
		shell->status_exit = status;
		return (status);
	}
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		exec_fork_child(shell, ast);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		shell->status_exit = 128 + WTERMSIG(status);
	else
		shell->status_exit = WEXITSTATUS(status);
	return (shell->status_exit);
}
