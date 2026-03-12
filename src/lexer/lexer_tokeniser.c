/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokeniser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 20:23:09 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/10 16:07:00 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	lex_tokeniser(char *input, size_t *idx)
{
	if (input[*idx] == '(')
		return (TOKEN_LPAREN);
	if (input[*idx] == ')')
		return (TOKEN_RPAREN);
	if (input[*idx] == '<' && input[*idx + 1] == '<')
		return (TOKEN_HERE_DOC);
	if (input[*idx] == '<')
		return (TOKEN_IN);
	if (input[*idx] == '>' && input[*idx + 1] == '>')
		return (TOKEN_APPEND_OUT);
	if (input[*idx] == '>')
		return (TOKEN_OUT);
	if (input[*idx] == '|' && input[*idx + 1] == '|')
		return (TOKEN_OR);
	if (input[*idx] == '|')
		return (TOKEN_PIPE);
	if (input[*idx] == '&' && input[*idx + 1] == '&')
		return (TOKEN_AND);
	if (input[*idx] == '\0')
		return (TOKEN_EOF);
	else
		return (TOKEN_WORD);
}
