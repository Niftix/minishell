#include "parser.h"

int	check_ast_is_redirect(t_token type)
{
	return (type == TOKEN_IN || type == TOKEN_OUT
		|| type == TOKEN_APPEND_OUT || type == TOKEN_HERE_DOC);
}

int	check_ast_is_cmd(t_token type)
{
	return (type == TOKEN_WORD || redirect_checker(type));
}

t_redirect_type	ast_to_redirect(t_token type)
{
	if (type == TOKEN_IN)
		return (REDIR_IN);
	if (type == TOKEN_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_APPEND_OUT)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

int	ast_add_redirect(t_lexer **cur, t_redirect **list)
{
	t_redirect_type	rtype;
	t_redirect		*redir;

	rtype = token_to_redir((*cur)->type);
	*cur = (*cur)->next;
	if (!*cur || (*cur)->type != TOKEN_WORD)
		return (1);
	redir = redirect_new(rtype, (*cur)->value);
	if (!redir)
		return (1);
	redirect_add_end(list, redir);
	*cur = (*cur)->next;
	return (0);
}
