/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_if_need_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 12:31:40 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/26 16:00:47 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	verif_if_need_expand(char *str)
{
	char	quote;

	quote = 'x';
	while (*str)
	{
		if (quote == 'x' && (*str == 39 || *str == 34))
			quote = *str;
		else if (*str == quote)
			quote = 'x';
		if (*str == '$' && quote != 39)
			return (1);
		str++;
	}
	return (0);
}
