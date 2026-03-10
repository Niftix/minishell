/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:12:18 by mville            #+#    #+#             */
/*   Updated: 2026/03/10 20:12:53 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	sub_child(t_shell *shell, t_ast *ast)
{
	int	status;

	gest_signal();
	if (ast->redirects && all_redirects(ast->redirects))
		exit(1);
	status = ast_dispatch(shell, ast->left);
	exit(status);
}

int	exec_subshell(t_shell *shell, t_ast *ast)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		sub_child(shell, ast);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		shell->status_exit = 128 + WTERMSIG(status);
	else
		shell->status_exit = WEXITSTATUS(status);
	return (shell->status_exit);
}
