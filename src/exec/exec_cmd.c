/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:16:54 by mville            #+#    #+#             */
/*   Updated: 2026/03/10 11:55:22 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_shell *shell, t_ast *ast)
{
	int		status;
	char	*path;
	pid_t	pid;

 if (!ast->args_cmd || !ast->args_cmd[0])
		return (0);
	if (check_builtins(ast->args_cmd[0]))
		return (exec_builtins(shell, ast));
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		path = find_cmd_path(shell, ast);
		if (!path)
			exit(127);
		execve(path, ast->args_cmd, shell->env);
		free(path);
		exit(126);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
