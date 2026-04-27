/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_set_exp_extract_var.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:52:43 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/26 15:56:13 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	exp_set_exp_extract_var(char *quote, size_t *start, char *str,
			size_t *idx)
{
	size_t i;

	*quote = 'x';
	*start = *idx;
	i = -1;
	while (++i < *idx)
	{
		if (*quote == 'x' && (str[i] == 39 || str[i] == 34))
			*quote = str[i];
		else if (str[i] == *quote)
			*quote = 'x';
	}
	if (*quote == 'x')
		*idx = exp_skip_tab_space_nl(str, *idx);
}
