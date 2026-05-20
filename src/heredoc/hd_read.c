/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:43:31 by mville            #+#    #+#             */
/*   Updated: 2026/05/20 18:15:29 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*read_hd_line(void)
{
	char	*line;
	char	*clean_line;

	if (isatty(STDIN_FILENO))
		return (readline("heredoc > "));
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	clean_line = ft_strtrim(line, "\n");
	free(line);
	return (clean_line);
}

static int	read_hd_child(t_redirect *redir, t_shell *shell, int expand)
{
	char	*line;

	signal(SIGINT, sigint_hd);
	while (1)
	{
		line = read_hd_line();
		if (g_status == 2)
		{
			free(line);
			child_exit(shell, 130);
		}
		if (!line || ft_strcmp(line, redir->target) == 0)
		{
			if (!line)
				put_hd_none_line_error(redir->target);
			free(line);
			child_exit(shell, 0);
		}
		if (write_line_hd(redir, shell, line, expand))
			(free(line), child_exit(shell, 1));
	}
	return (0);
}

static int	read_hd_parent(t_redirect *redir, t_shell *shell, int expand,
	char *name)
{
	char	*line;

	while (1)
	{
		line = read_hd_line();
		if (!line || ft_strcmp(line, redir->target) == 0)
		{
			if (!line)
				put_hd_none_line_error(redir->target);
			free(line);
			break ;
		}
		if (write_line_hd(redir, shell, line, expand))
			return (hd_fail(redir, name));
	}
	return (close_hd(redir, name));
}

static int	wait_hd_child(t_redirect *redir, char *name, int status)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_status = SIGINT;
		return (hd_fail(redir, name));
	}
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (hd_fail(redir, name));
	return (close_hd(redir, name));
}

int	read_hd(t_redirect *redir, t_shell *shell)
{
	char	*name;
	int		expand;
	int		status;
	pid_t	pid;
	pid_t	waited;

	expand = check_quote(redir);
	name = create_hd(redir);
	if (!name)
		return (1);
	if (!isatty(STDIN_FILENO))
		return (read_hd_parent(redir, shell, expand, name));
	pid = fork();
	if (pid < 0)
		return (hd_fail(redir, name));
	if (pid == 0)
		(free(name), read_hd_child(redir, shell, expand));
	parent_wait_signal();
	waited = waitpid(pid, &status, 0);
	while (waited == -1 && errno == EINTR)
		waited = waitpid(pid, &status, 0);
	signal_interactive();
	if (waited == -1)
		return (hd_fail(redir, name));
	return (wait_hd_child(redir, name, status));
}
