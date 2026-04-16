/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_group.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:12:18 by mville            #+#    #+#             */
/*   Updated: 2026/04/14 17:25:27 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_group(t_shell *shell, t_ast *ast)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
	{
		gest_signal();
		if (ast->redirects && all_redirects(ast->redirects))
			child_exit(shell, 1);
		status = ast_dispatch(shell, ast->left);
		child_exit(shell, status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->status_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->status_exit = 128 + WTERMSIG(status);
	return (shell->status_exit);
}
