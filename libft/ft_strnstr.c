/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:19:21 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/06 21:19:21 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *tab, const char *chr, size_t n)
{
	size_t	i;
	size_t	y;

	if (!*chr)
		return ((char *)tab);
	if (!tab && n == 0)
		return (NULL);
	i = 0;
	while (i < n && tab[i])
	{
		y = 0;
		while (chr[y] && (i + y < n) && tab[i + y] == chr[y])
			y++;
		if (!chr[y])
			return ((char *)tab + i);
		i++;
	}
	return (NULL);
}
