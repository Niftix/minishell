/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 20:43:27 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/15 15:51:19 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	valid_redirect(t_lexer *now)
{
	if (now->next->type == TOKEN_WORD)
		return (0);
	return (2);
}

static int	valid_comp(t_lexer *prev, t_lexer *now)
{
	t_lexer	*next;

	if (prev == NULL)
		return (1);
	next = now->next;
	if (now->type == TOKEN_PIPE)
	{
		if (next->type == TOKEN_EOF)
			return (2);
		if ((prev->type == TOKEN_RPAREN || prev->type == TOKEN_WORD)
			&& (next->type == TOKEN_LPAREN || next->type == TOKEN_WORD
			|| next->type == TOKEN_IN || next->type == TOKEN_HERE_DOC
			|| next->type == TOKEN_OUT || next->type == TOKEN_APPEND_OUT))
			return (0);
	}
	else
	{	
		if (next->type == TOKEN_EOF)
			return (2);
		if ((prev->type == TOKEN_RPAREN || prev->type == TOKEN_WORD)
			&& (next->type == TOKEN_LPAREN || next->type == TOKEN_WORD))
			return (0);
	}
	return (1);
}

static int	valid_open_parent(t_lexer *now)
{
	t_lexer	*tmp;
	int		o_parent;

	if (now->next->type == TOKEN_RPAREN)
		return (0);
	o_parent = 1;
	tmp = now->next;
	while (1)
	{
		if (tmp->type == TOKEN_EOF || o_parent == 0)
			break ;
		if (tmp->type == TOKEN_RPAREN)
			o_parent--;
		if (tmp->type == TOKEN_LPAREN)
			o_parent++;
		tmp = tmp->next;
	}
	if (o_parent == 0)
		return (0);
	return (2);
}

static int	valid_parent(t_lexer *lexer, t_lexer *now)
{
	t_lexer	*tmp;
	int		c_parent;

	if (now->type == TOKEN_LPAREN)
		return (valid_open_parent(now));
	tmp = lexer;
	c_parent = -1;
	while (tmp != now)
	{
		if (tmp->type == TOKEN_RPAREN)
			c_parent--;
		if (tmp->type == TOKEN_LPAREN)
			c_parent++;
		if (tmp->next == now && c_parent == 0 && (tmp->type == TOKEN_LPAREN
				&& now->type == TOKEN_RPAREN))
			return (1);
		tmp = tmp->next;
	}
	if (c_parent == 0)
		return (0);
	return (1);
}

int	lex_pars_elements(t_lexer *lexer, t_lexer *prev, t_lexer *now)
{
	int	check;

	check = 0;
	if (now->type == TOKEN_IN || now->type == TOKEN_OUT
		|| now->type == TOKEN_APPEND_OUT || now->type == TOKEN_HERE_DOC)
		check = valid_redirect(now);
	if (now->type == TOKEN_AND || now->type == TOKEN_OR
		|| now->type == TOKEN_PIPE)
		check = valid_comp(prev, now);
	if (now->type == TOKEN_LPAREN || now->type == TOKEN_RPAREN)
		check = valid_parent(lexer, now);
	return (check);
}
