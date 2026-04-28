/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:31:30 by mville            #+#    #+#             */
/*   Updated: 2026/04/28 16:45:34 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static char	*get_redir_target(t_lexer *cur, t_shell *shell)
{
	char	**words;
	char	*tmp;
	char	*target;

	tmp = ft_strdup(cur->value);
	if (!tmp)
		return (NULL);
	words = expand(tmp, shell->env, shell->status_exit);
	if (!words || !words[0] || words[1] || words[0][0] == '\0')
	{
		error_ambiguous_redirect(cur->value, shell);
		return (ft_free_tab(words), NULL);
	}
	target = remove_quote(words[0]);
	if (ft_strchr(cur->value, '$') && !ft_strchr(cur->value, '\'')
		&& !ft_strchr(cur->value, '"') && target && (ft_strchr(target, ' ')
			|| ft_strchr(target, '\t')))
	{
		error_ambiguous_redirect(cur->value, shell);
		free(target);
		return (ft_free_tab(words), NULL);
	}
	ft_free_tab(words);
	return (target);
}

int	parse_one_redirect(t_lexer **cur, t_redirect **list, t_shell *shell)
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
		target = get_redir_target(*cur, shell);
	if (!target)
		return (1);
	if (rtype == REDIR_IN || rtype == REDIR_HEREDOC)
		redir = redirect_new(rtype, target, STDIN_FILENO);
	else
		redir = redirect_new(rtype, target, STDOUT_FILENO);
	free(target);
	if (!redir)
		return (1);
	redirect_add_end(list, redir);
	*cur = (*cur)->next;
	return (0);
}
