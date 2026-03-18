#include "minishell.h"


t_ast	*check_parse(t_lexer *lex)
{
	if (!lex || lex->type == TOKEN_ERROR || lex->type == TOKEN_EOF)
		return (NULL);
	return (parse_and_or(&lex));
}
