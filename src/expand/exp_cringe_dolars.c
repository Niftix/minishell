/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_cringe_dolars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:59:18 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/16 17:33:37 by vcucuiet         ###   ########.fr       */
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
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	quote = 'x';
	while (i < len)
	{
		if ((str[i] == '\"' || str[i] == '\'') && quote == 'x')
			quote = str[i];
		else if (str[i] == quote)
			quote = 'x';
		if ((str[i] == '$' && quote == 'x')
			&& ((str[i + 1] == '"' || str[i + 1] == '\'') && quote == 'x'))
			str = exp_rm_cringe_dolars(str, i);
		else
			i++;
	}
	return (str);
}
