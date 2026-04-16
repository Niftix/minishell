/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars_valid_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:41:08 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/16 16:45:03 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lex_pars_valid_word(char *str)
{
	size_t	i;
	char	quote;

	quote = 'x';
	i = -1;
	while (str[++i])
	{
		if (quote == 'x' && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == quote)
			quote = 'x';
	}
	if (quote == 'x')
		return (0);
	return (3);
}
