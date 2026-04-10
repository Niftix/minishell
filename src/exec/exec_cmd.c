/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:16:54 by mville            #+#    #+#             */
/*   Updated: 2026/04/10 13:10:11 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execve_fail_exit(t_shell *shell, t_ast *ast, char *path)
{
	if (check_dir(path))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ast->args_cmd[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(path);
		child_exit(shell, 126);
	}
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(ast->args_cmd[0], 2);
	ft_putstr_fd(": permission denied\n", 2);
	free(path);
	child_exit(shell, 126);
}

static void	path_null_exit(t_shell *shell, t_ast *ast)
{
	if (!ft_strchr(ast->args_cmd[0], '/'))
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(ast->args_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		child_exit(shell, 127);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(ast->args_cmd[0], 2);
	if (check_dir(ast->args_cmd[0]))
		return (ft_putstr_fd(": Is a directory\n", 2),
			child_exit(shell, 126));
	if (access(ast->args_cmd[0], F_OK) == 0)
		return (ft_putstr_fd(": Permission denied\n", 2),
			child_exit(shell, 126));
	ft_putstr_fd(": No such file or directory\n", 2);
	child_exit(shell, 127);
}

static void	exec_fork_child(t_shell *shell, t_ast *ast)
{
	char	*path;

	gest_signal();
	if (ast->redirects && all_redirects(ast->redirects))
		child_exit(shell, 1);
	path = find_cmd_path(shell, ast);
	if (!path)
		path_null_exit(shell, ast);
	execve(path, ast->args_cmd, shell->env);
	execve_fail_exit(shell, ast, path);
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

	if (!ast->args_cmd || !ast->args_cmd[0] || !ast->args_cmd[0][0])
		return (0);
	status = builtin_assign(shell, ast);
	if (status != -1)
	{
		shell->status_exit = status;
		return (status);
	}
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
