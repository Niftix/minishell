/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars_valid_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:41:08 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/29 11:21:26 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	lex_put_brace_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": bad substitution\n", 2);
	return (3);
}

static int	lex_verif_brace(char *str)
{
	size_t i;
	int		brace;
	int		tracer;

	i = 0;
	if (str[0] == '}')
		return (3);
	tracer = 1;
	brace = 1;
	while (str[i] && brace && tracer &&
			(ft_isalnum(str[i]) || str[i] == '{' || str[i] == '}' || str[i] == '_'))
	{
		if (str[i] == '{')
			brace++;
		if (str[i] == '{' && tracer)
			tracer--;
		if (str[i] == '}')
			brace--;
		i++;
	}
	if (tracer != 1)
		return (3);
	if (brace != 0)
		return (2);
	return (0);
}

static int	lex_varif_valid_variable(char *str, int i)
{
	if (str[i + 1] == '{')
		 return (lex_verif_brace(str + i + 2));
	return (0);
}

int	lex_pars_valid_word(char *str)
{
	size_t	i;
	char	quote;
	int		check;

	quote = 'x';
	i = -1;
	check = 0;
	while (str[++i])
	{
		if (quote == 'x' && (str[i] == 34 || str[i] == 39))
			quote = str[i];
		else if (str[i] == quote)
			quote = 'x';
		if (str[i] == '$' && quote != 39 && !check)
			check = lex_varif_valid_variable(str, i);
	}
	if (quote != 'x')
		return (3);
	if (check == 3)
		lex_put_brace_error(str);
	return (check);
}
