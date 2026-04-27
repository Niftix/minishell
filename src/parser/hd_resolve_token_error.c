/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_resolve_token_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:12:47 by mville            #+#    #+#             */
/*   Updated: 2026/04/23 17:13:07 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_redirection(t_redirect *redirection)
{
	if (!redirection)
		return ;
	if (redirection->fd != -1)
		close(redirection->fd);
	free(redirection->target);
	free(redirection);
}

int	resolve_token_error_with_hd(t_lexer *lex, t_shell *shell)
{
	t_redirect	*redirection;

	while (lex)
	{
		if (lex->type == TOKEN_HERE_DOC && lex->next
			&& lex->next->type == TOKEN_WORD)
		{
			redirection = redirect_new(REDIR_HEREDOC, lex->next->value,
					STDIN_FILENO);
			if (!redirection)
				return (1);
			if (read_hd(redirection, shell))
			{
				redirection->fd = -1;
				return (free_redirection(redirection), 1);
			}
			free_redirection(redirection);
			lex = lex->next;
		}
		lex = lex->next;
	}
	return (0);
}
