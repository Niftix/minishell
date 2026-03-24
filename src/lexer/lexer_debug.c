/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:27:56 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/24 14:51:50 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*    All the following ft arr use only for debug use only one lexer debug    */

#include "lexer.h"

static void	lex_print_token_t2(t_token token)
{
	if (token == TOKEN_ERROR)
		printf("lexer: token = ERROR");
	else
		printf("BIG ERROR BRO YOUR NOT SUPPOSE TO SEE THIS");
}

void	lex_print_token_type(t_token token)
{
	if (token == TOKEN_AND)
		printf("lexer :token = [&&]");
	else if (token == TOKEN_OR)
		printf("lexer: token = [||]");
	else if (token == TOKEN_PIPE)
		printf("lexer: token = [|]");
	else if (token == TOKEN_APPEND_OUT)
		printf("lexer: token = [>>]");
	else if (token == TOKEN_HERE_DOC)
		printf("lexer: token = [<<]");
	else if (token == TOKEN_IN)
		printf("lexer: token = [<]");
	else if (token == TOKEN_LPAREN)
		printf("lexer: token = [(]");
	else if (token == TOKEN_RPAREN)
		printf("lexer: token = [)]");
	else if (token == TOKEN_OUT)
		printf("lexer: token = [>]");
	else if (token == TOKEN_EOF)
		printf("lexer: token = [EOF]");
	else if (token == TOKEN_WORD)
		printf("lexer: token = [WORD]");
	else
		lex_print_token_t2(token);
}

void	lex_print_all(t_lexer	*lexer)
{
	while (lexer)
	{
		lex_print_token_type(lexer->type);
		if (lexer->value)
			printf (" = [%s]", lexer->value);
		printf ("\n");
		lexer = lexer->next;
	}
}
