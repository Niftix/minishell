/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_set_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:25:35 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/10 14:47:18 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static size_t	set_buf(char *buf, char *input, size_t *idx)
{
	size_t		i;
	int			in_q;
	char		quote;

	quote = 'x';
	i = -1;
	while (++i < LEXER_BUF && input[*idx])
	{
		if (quote == 'x' && (input[*idx] == '\'' || input[*idx] == '\"'))
			quote = input[*idx];
		else if (input[*idx] == quote)
			quote = 'x';
		if ((quote == 'x' && input[*idx] == ' ')
			|| (!in_q && tokeniser(input, idx) != TOKEN_WORD))
			return (*idx += 1, i);	
		buf[i] = input[*idx];
		*idx += 1;
	}
	return (i);
}

static char	*set_value(char *input, size_t idx)
{
	char	*val;
	char	*buf;
	int		t_cpy;
	ssize_t	val_len;

	val = NULL;
	val_len = 0;
	buf = malloc(sizeof(char) * (LEXER_BUF + 1));
	if (!buf)
		return (NULL);
	while(1)
	{
		t_cpy = set_buf(buf, input, &idx);
		buf[t_cpy] = '\0';
		val = ft_strdupcat(val, buf, &val_len, t_cpy);
		if (!val)
			return (free(buf), NULL);
		if (t_cpy != LEXER_BUF)
			break ;
	}
	free(buf);
	buf = NULL;
	return (val);
}
