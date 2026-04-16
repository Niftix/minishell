/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:27:21 by mville            #+#    #+#             */
/*   Updated: 2026/04/11 00:08:46 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_token(t_lexer *lex)
{
	if (!lex || lex->type == TOKEN_EOF)
		return (ft_putstr_fd("'newline'\n", 2));
	if (lex->type == TOKEN_IN)
		return (ft_putstr_fd("'<'\n", 2));
	if (lex->type == TOKEN_OUT)
		return (ft_putstr_fd("'>'\n", 2));
	if (lex->type == TOKEN_OR)
		return (ft_putstr_fd("'||'\n", 2));
	if (lex->type == TOKEN_AND)
		return (ft_putstr_fd("'&&'\n", 2));
	if (lex->type == TOKEN_LPAREN)
		return (ft_putstr_fd("'('\n", 2));
	if (lex->type == TOKEN_RPAREN)
		return (ft_putstr_fd("')'\n", 2));
	if (lex->type == TOKEN_PIPE)
		return (ft_putstr_fd("'|'\n", 2));
	if (lex->type == TOKEN_HERE_DOC)
		return (ft_putstr_fd("'<<'\n", 2));
	if (lex->type == TOKEN_APPEND_OUT)
		return (ft_putstr_fd("'>>'\n", 2));
	if (lex->type == TOKEN_WORD)
		return (ft_putstr_fd(lex->value, 2), ft_putstr_fd("\n", 2));
}

void	parser_put_error(t_lexer *lex)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	print_token(lex);
}
