/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_resolve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:31:23 by mville            #+#    #+#             */
/*   Updated: 2026/04/07 14:02:41 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*remove_quote(char *str)
{
	char	*new;
	char	quote;
	int		i;
	int		j;

	new = malloc(ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	quote = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

static int	check_quote(t_redirect *redir)
{
	char	*stripped;
	int		expand;

	expand = 1;
	if (ft_strchr(redir->target, '\'') || ft_strchr(redir->target, '\"'))
	{
		stripped = remove_quote(redir->target);
		if (!stripped)
			return (expand);
		free(redir->target);
		redir->target = stripped;
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

int	read_hd(t_redirect *redir, t_shell *shell)
{
	char	*line;
	char	*name;

	(void)shell;
	check_quote(redir);
	name = create_hd(redir);
	if (!name)
		return (1);
	while (1)
	{
		line = readline("heredoc > ");
		if (!line || ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, redir->fd);
		ft_putstr_fd("\n", redir->fd);
		free(line);
	}
	close(redir->fd);
	redir->fd = open(name, O_RDONLY);
	unlink(name);
	free(name);
	return (0);
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
