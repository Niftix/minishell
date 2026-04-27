/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars_valid_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:41:08 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/27 18:03:53 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	lex_put_brace_error()
{
	
	return (3);
}

static char	lex_get_quote_state(char *str, size_t idx)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 'x';
	while (i < idx)
	{
		if (quote == 'x' && (str[i] == 39 || str[i] == 34))
			quote = str[i];
		else if (str[i] == quote)
			quote = 'x';
		i++;
	}
	return (quote);
}

static int	lex_verif_brace(char *str)
{
	size_t i;
	int		brace;
	int		tracer;

	i = 0;
	if (str[0] == '{')
	{
		tracer = 1;
		brace = 1;
		while (str[i] && brace && tracer)
		{
			if (str[i] == '{')
				brace++;
			if (str[i] == '{' && brace)
				tracer++;
			if (str[i] == '{')
				brace--;
			i++;
		}
		if (str[i] != '}')
			return (2);
		if (tracer != 1)
			return (lex_put_brace_error());
	}
	return (0);
}

static int	lex_varif_valid_variable(char *str)
{
	size_t	i;
	int		check;

	i = -1;
	check = 0;
	while (str[++i])
	{
		if (str[i] == '$' && lex_get_quote_state(str, i) != 39)
		 	check = lex_verif_brace(str + i);
		if (check)
			return (check);
	}
	return (0);
}

int	lex_pars_valid_word(char *str)
{
	size_t	i;
	char	quote;

	quote = 'x';
	i = -1;
	while (str[++i])
	{
		if (quote == 'x' && (str[i] == 34 || str[i] == 39))
			quote = str[i];
		else if (str[i] == quote)
			quote = 'x';
	}
	if (quote != 'x')
		return (3);
	return (lex_varif_valid_variable(str));
}
