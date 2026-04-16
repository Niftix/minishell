/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:31:30 by mville            #+#    #+#             */
/*   Updated: 2026/04/10 12:23:02 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	redir_fd_target(t_redirect_type type)
{
	if (type == REDIR_IN || type == REDIR_HEREDOC)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

int	redirect_checker(t_token type)
{
	return (type == TOKEN_IN || type == TOKEN_OUT
		|| type == TOKEN_APPEND_OUT || type == TOKEN_HERE_DOC);
}

int	cmd_token_checker(t_token type)
{
	return (type == TOKEN_WORD || redirect_checker(type));
}

t_redirect_type	token_to_redir(t_token type)
{
	if (type == TOKEN_IN)
		return (REDIR_IN);
	if (type == TOKEN_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_APPEND_OUT)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

int	parse_one_redirect(t_lexer **cur, t_redirect **list)
{
	t_redirect_type	rtype;
	t_redirect		*redir;
	char			*target;

	rtype = token_to_redir((*cur)->type);
	*cur = (*cur)->next;
	if (!*cur || (*cur)->type != TOKEN_WORD)
		return (1);
	if (rtype == REDIR_HEREDOC)
		target = ft_strdup((*cur)->value);
	else
		target = remove_quote((*cur)->value);
	redir = redirect_new(rtype, target, redir_fd_target(rtype));
	free(target);
	if (!redir)
		return (1);
	redirect_add_end(list, redir);
	*cur = (*cur)->next;
	return (0);
}
