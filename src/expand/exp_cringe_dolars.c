/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_cringe_dolars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:59:18 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/10 18:02:14 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*exp_rm_cringe_dolars(char *str, size_t idx)
{
	while (str[idx + 1])
	{
		str[idx] = str[idx + 1];
		idx++;
	}
	str[idx] = '\0';
	return (str);
}

char	*exp_cringe_dolars(char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 'x';
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && quote == 'x')
			quote = str[i];
		if (str[i] == quote)
			quote = 'x';
		if (str[i] == '$' && quote == 'x')
		{
			if ((str[i + 1] == '"' || str[i + 1] == '\'') && quote == 'x')
				str = exp_rm_cringe_dolars(str, i);
			i -= 2;
		}
		i++;
	}
	return (str);
}