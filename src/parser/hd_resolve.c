/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_resolve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:31:23 by mville            #+#    #+#             */
/*   Updated: 2026/04/23 18:43:49 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_quote(t_redirect *redir)
{
	char	*clean_target;
	int		expand;

	expand = 1;
	if (ft_strchr(redir->target, '\'') || ft_strchr(redir->target, '\"'))
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

static char	*create_hd(t_redirect *redir)
{
	static int	i;
	char		*name;
	char		*tmp;

	tmp = ft_itoa(i++);
	name = ft_strjoin("/tmp/hd_", tmp);
	free(tmp);
	if (!name)
		return (NULL);
	if (redir->fd == -1)
		redir->fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd < 0)
		perror("open");
	return (name);
}

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

int	read_hd(t_redirect *redir, t_shell *shell)
{
	char	*line;
	char	*name;
	int		expand;

	expand = check_quote(redir);
	name = create_hd(redir);
	if (!name)
		return (1);
	while (1)
	{
		line = read_hd_line();
		if (!line || ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			break ;
		}
		if (write_line_hd(redir, shell, line, expand))
			return (close(redir->fd), free(name), 1);
	}
	return (close_hd(redir, name));
}

int	hd_resolve(t_ast *ast, t_shell *shell)
{
	t_redirect	*tmp;

	if (!ast)
		return (0);
	tmp = ast->redirects;
	if (hd_resolve(ast->left, shell))
		return (1);
	if (hd_resolve(ast->right, shell))
		return (1);
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC)
			if (read_hd(tmp, shell))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}
