/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:40:00 by mville            #+#    #+#             */
/*   Updated: 2026/04/16 15:50:27 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_execve_fail(t_shell *shell, t_ast *ast, char *path)
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

static void	pipe_path_error(t_shell *shell, t_ast *ast)
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

static int	exec_pipe_command(t_shell *shell, t_ast *ast)
{
	char	*path;
	char	**exec_env;

	if (!ast->args_cmd || !ast->args_cmd[0] || !ast->args_cmd[0][0])
		return (0);
	if (ast->redirects && all_redirects(ast->redirects))
		return (1);
	if (check_builtins(ast->args_cmd[0]))
		return (exec_builtins(shell, ast));
	path = resolve_cmd_path(shell, ast);
	if (!path)
		pipe_path_error(shell, ast);
	exec_env = build_exec_env(shell);
	if (!exec_env)
		return (free(path), 1);
	execve(path, ast->args_cmd, exec_env);
	free(exec_env);
	pipe_execve_fail(shell, ast, path);
	return (126);
}

void	left_pipe_writer(t_shell *shell, t_ast *ast, int *fd)
{
	int	status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (ast->left && ast->left->type == AST_CMD)
		status = exec_pipe_command(shell, ast->left);
	else
		status = ast_dispatch(shell, ast->left);
	child_exit(shell, status);
}

void	right_pipe_reader(t_shell *shell, t_ast *ast, int *fd)
{
	int	status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (ast->right && ast->right->type == AST_CMD)
		status = exec_pipe_command(shell, ast->right);
	else
		status = ast_dispatch(shell, ast->right);
	child_exit(shell, status);
}
