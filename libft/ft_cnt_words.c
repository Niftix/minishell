/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnt_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:20:58 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/02/03 11:39:38 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_cnt_words(const char *str)
{
	int	cnt;
	int	i;

	if (!str)
		return (0);
	cnt = 0;
	i = -1;
	while (str[++i])
	{
		while (str[i] && ft_is_space(str[i]))
			i++;
		if (str[i])
			cnt++;
		while (str[i] && !ft_is_space(str[i]))
			i++;
	}
	return (cnt);
}
