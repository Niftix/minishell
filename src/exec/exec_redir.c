/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:52:17 by mville            #+#    #+#             */
/*   Updated: 2026/04/14 17:25:28 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_in(char *target, int fd_target)
{
	int	fd;

	fd = open(target, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	dup2(fd, fd_target);
	close(fd);
	return (0);
}

static int	redir_out(char *target, int append, int fd_target)
{
	int	fd;
	int	flags;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(target, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	dup2(fd, fd_target);
	close(fd);
	return (0);
}

static int	redir_heredoc(t_redirect *redirect)
{
	if (redirect->fd < 0)
		return (1);
	dup2(redirect->fd, redirect->fd_target);
	close(redirect->fd);
	redirect->fd = -1;
	return (0);
}

static int	apply_one_redirect(t_redirect *current)
{
	if (current->type == REDIR_IN)
		return (redir_in(current->target, current->fd_target));
	if (current->type == REDIR_OUT)
		return (redir_out(current->target, 0, current->fd_target));
	if (current->type == REDIR_APPEND)
		return (redir_out(current->target, 1, current->fd_target));
	if (current->type == REDIR_HEREDOC)
		return (redir_heredoc(current));
	return (0);
}

int	all_redirects(t_redirect *redirects)
{
	t_redirect	*current;

	current = redirects;
	while (current)
	{
		if (apply_one_redirect(current))
			return (1);
		current = current->next;
	}
	return (0);
}
