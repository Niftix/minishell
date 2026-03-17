/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 20:07:59 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/14 20:48:32 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"



void lex_print_token_error(t_token token)
{
	if(token == TOKEN_IN)
		return (ft_putstr_fd("'<'\n", 2));
	if(token == TOKEN_OUT)
		return (ft_putstr_fd("'>'\n", 2));
	if(token == TOKEN_OR)
		return (ft_putstr_fd("'||'\n", 2));
	if(token == TOKEN_AND)
		return (ft_putstr_fd("'&&'\n", 2));
	if(token == TOKEN_LPAREN)
		return (ft_putstr_fd("'('\n", 2));
	if(token == TOKEN_RPAREN)
		return (ft_putstr_fd("')'\n", 2));
	if(token == TOKEN_PIPE)
		return (ft_putstr_fd("'|'\n", 2));
	if(token == TOKEN_HERE_DOC)
		return (ft_putstr_fd("'<<'\n", 2));
	if(token == TOKEN_APPEND_OUT)
		return (ft_putstr_fd("'>>'\n", 2));
}

t_lexer	*lex_pars_error(t_lexer *tmp, t_lexer *lex)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	lex_print_token_error(tmp->type);
	free(lex);
	lex = malloc(sizeof(t_lexer));
	if (!lex)
		return(NULL);
	lex->next = NULL;
	lex->value = NULL;
	lex->type = TOKEN_ERROR;
	return (lex);
}

t_lexer	*lex_pars(t_lexer *lex)
{
	t_lexer	*tmp;
	t_lexer	*prev;

	prev = NULL;
	tmp = lex;
	while (tmp->type != TOKEN_EOF)
	{
		if (lex_pars_elements(prev, tmp))
			return (lex_pars_error(tmp, lex));
		tmp = tmp->next;
	}
	return (lex);
}
