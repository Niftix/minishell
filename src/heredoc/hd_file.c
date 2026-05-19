/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:43:25 by mville            #+#    #+#             */
/*   Updated: 2026/05/19 10:59:01 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_quote(t_redirect *redir)
{
	char	*clean_target;
	int		expand;

	expand = 1;
	if (ft_strchr(redir->target, 39) || ft_strchr(redir->target, 34))
	{
		clean_target = remove_quote(redir->target);
		if (!clean_target)
			return (expand);
		free(redir->target);
		redir->target = clean_target;
		expand = 0;
	}
	return (expand);
}

char	*create_hd(t_redirect *redir)
{
	static int	i;
	char		*name;
	char		*idx;

	while (1)
	{
		idx = ft_itoa(i++);
		if (!idx)
			return (NULL);
		name = ft_strjoin("/tmp/hd_", idx);
		free(idx);
		if (!name)
			return (NULL);
		redir->fd = open(name, O_WRONLY | O_CREAT | O_EXCL, 0644);
		if (redir->fd >= 0)
			return (name);
		free(name);
		if (errno != EEXIST)
		{
			perror("open");
			return (NULL);
		}
	}
}

int	close_hd(t_redirect *redir, char *name)
{
	close(redir->fd);
	redir->fd = open(name, O_RDONLY);
	if (redir->fd < 0)
		return (free(name), 1);
	unlink(name);
	free(name);
	return (0);
}
