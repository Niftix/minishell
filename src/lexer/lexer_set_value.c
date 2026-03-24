/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_set_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:25:35 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/23 13:31:13 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static ssize_t	lex_quote_verif(char *quote)
{
	if (*quote == 'x')
		return (0);
	ft_putstr_fd("Minishell: lexer: error: unclosed quote\n", 2);
	return (*quote = 'x', -1);
}

static ssize_t	lex_set_buf(char *buf, char *input, size_t *idx)
{
	size_t		i;
	static char	quote = 'x';

	if (!buf || !input)
		return (lex_quote_verif(&quote));
	i = -1;
	while (++i < LEXER_BUF && input[*idx])
	{
		if (quote == 'x' && (input[*idx] == '\'' || input[*idx] == '\"'))
			quote = input[*idx];
		else if (input[*idx] == quote)
			quote = 'x';
		if ((quote == 'x' && input[*idx] == ' ') || (quote == 'x'
				&& lex_tokeniser(input, idx) != TOKEN_WORD))
			return (*idx += 1, i);
		buf[i] = input[*idx];
		*idx += 1;
	}
	return (i);
}

static char	*lex_cpy_value_from_input(char *buf, char *input, size_t idx)
{
	ssize_t	t_cpy;
	ssize_t	val_len;
	char	*val;

	val = NULL;
	t_cpy = 0;
	val_len = 0;
	while (1)
	{
		t_cpy = lex_set_buf(buf, input, &idx);
		if (t_cpy < 0)
			return (free(val), NULL);
		buf[t_cpy] = '\0';
		val = ft_strdupcat(val, buf, &val_len, t_cpy);
		if (!val)
			return (NULL);
		if (t_cpy != LEXER_BUF)
		{
			if (lex_set_buf(NULL, NULL, 0) == -1)
				return (free(val), NULL);
			break ;
		}
	}
	return (val);
}

char	*lex_set_value(char *input, size_t idx)
{
	char	*val;
	char	*buf;

	val = NULL;
	buf = malloc(sizeof(char) * (LEXER_BUF + 1));
	if (!buf)
		return (NULL);
	val = lex_cpy_value_from_input(buf, input, idx);
	free(buf);
	buf = NULL;
	return (val);
}
