/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_if_need_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 12:31:40 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/31 12:31:50 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	verif_if_need_expand(char *str)
{
	char	quote;

	quote = 'x';
	while (*str)
	{
		if (quote == 'x' && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (*str == quote)
			quote = 'x';
		if (*str == '$' && quote != '\'')
			return (1);
		str++;
	}
	return (0);
}
