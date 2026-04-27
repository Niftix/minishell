/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 11:35:51 by mville            #+#    #+#             */
/*   Updated: 2026/04/18 09:27:16 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_redirect_only(t_shell *shell, t_ast *ast)
{
	int	status;

	if (!ast->redirects)
		return (0);
	if (fd_save(shell))
		return (1);
	if (all_redirects(ast->redirects))
		return (fd_recovery(shell), shell->status_exit = 1, 1);
	status = 0;
	fd_recovery(shell);
	shell->status_exit = status;
	return (status);
}

static int	exec_empty_cmd(t_shell *shell, t_ast *ast)
{
	if (ast->redirects)
	{
		if (fd_save(shell))
			return (1);
		if (all_redirects(ast->redirects))
			return (fd_recovery(shell), shell->status_exit = 1, 1);
		fd_recovery(shell);
	}
	ft_putstr_fd("minishell: : command not found\n", 2);
	shell->status_exit = 127;
	return (127);
}

static int	exec_builtin(t_shell *shell, t_ast *ast)
{
	int	status;

	if (ast->redirects)
	{
		if (fd_save(shell))
			return (1);
		if (all_redirects(ast->redirects))
			return (fd_recovery(shell), 1);
		status = exec_builtins(shell, ast);
		fd_recovery(shell);
	}
	else
		status = exec_builtins(shell, ast);
	shell->status_exit = status;
	return (status);
}

int	exec_cmd(t_shell *shell, t_ast *ast)
{
	int		status;
	pid_t	pid;

	if (!ast->args_cmd || !ast->args_cmd[0])
		return (exec_redirect_only(shell, ast));
	if (!ast->args_cmd[0][0])
		return (exec_empty_cmd(shell, ast));
	if (check_builtins(ast->args_cmd[0]))
		return (exec_builtin(shell, ast));
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
