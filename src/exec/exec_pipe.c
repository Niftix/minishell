/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:55:33 by mville            #+#    #+#             */
/*   Updated: 2026/03/09 20:48:45 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lchild(t_shell *shell, t_ast *ast, int *fd)
{
	int	status;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	status = ast_dispatch(shell, ast->left);
	exit(status);
}

static void	rchild(t_shell *shell, t_ast *ast, int *fd)
{
	int	status;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	status = ast_dispatch(shell, ast->right);
	exit(status);
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
		return (1);
	if (lpid == 0)
		lchild(shell, ast, fd);
	rpid = fork();
	if (rpid == -1)
		return (1);
	if (rpid == 0)
		rchild(shell, ast, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(lpid, &status, 0);
	waitpid(rpid, &status, 0);
	return (WEXITSTATUS(status));
}
