/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:16:54 by mville            #+#    #+#             */
/*   Updated: 2026/03/10 12:26:34 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void execve_fail_exit(t_ast *ast, char *path)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(ast->args_cmd[0], 2);
	ft_putstr_fd(": permission denied\n", 2);
	free(path);
	exit(126);
}

static void path_null_exit(t_ast *ast)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(ast->args_cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

static void gest_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

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
		gest_signal();
		path = find_cmd_path(shell, ast);
		if (!path)
			path_null_exit(ast);
		execve(path, ast->args_cmd, shell->env);
		execve_fail_exit(ast, path);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
