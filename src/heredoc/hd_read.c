/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:43:31 by mville            #+#    #+#             */
/*   Updated: 2026/05/17 15:32:51 by mville           ###   ########.fr       */
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
			exit(130);
		}
		if (!line || ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			exit(0);
		}
		if (write_line_hd(redir, shell, line, expand))
			exit(1);
	}
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
		g_status = 2;
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
		read_hd_child(redir, shell, expand);
	waitpid(pid, &status, 0);
	return (wait_hd_child(redir, name, status));
}
