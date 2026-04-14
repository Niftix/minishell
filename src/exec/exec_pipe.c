/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:55:33 by mville            #+#    #+#             */
/*   Updated: 2026/04/07 14:02:27 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	close_pipe(int *fd, int return_value)
{
	close(fd[0]);
	close(fd[1]);
	return (return_value);
}

static int	clean_fork(int *fd, pid_t lpid)
{
	kill(lpid, SIGTERM);
	waitpid(lpid, NULL, 0);
	return (close_pipe(fd, 1));
}

int	exec_pipe(t_shell *shell, t_ast *ast)
{
	pid_t	lpid;
	pid_t	rpid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		return (1);
	lpid = fork();
	if (lpid == -1)
		return (close_pipe(fd, 1));
	if (lpid == 0)
		left_pipe_writer(shell, ast, fd);
	rpid = fork();
	if (rpid == -1)
		return (clean_fork(fd, lpid));
	if (rpid == 0)
		right_pipe_reader(shell, ast, fd);
	close_pipe(fd, 0);
	waitpid(lpid, NULL, 0);
	waitpid(rpid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
