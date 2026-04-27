/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 22:43:26 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/26 15:56:26 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	exp_get_quote_state(char *str, size_t idx)
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