#include "minishell.h"

int	redirect_checker(t_token type)
{
	return (type == TOKEN_IN || type == TOKEN_OUT
		|| type == TOKEN_APPEND_OUT || type == TOKEN_HERE_DOC);
}

int	cmd_token_checker(t_token type)
{
	return (type == TOKEN_WORD || redirect_checker(type));
}

int	count_words(t_lexer *current)
{
	int	count;

	count = 0;
	while (cmd_token_checker(current->type))
	{
		if (current->type == TOKEN_WORD)
			count++;
		else
			current = current->next;
		current = current->next;
	}
	return (count);
}
