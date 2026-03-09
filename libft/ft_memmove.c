/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:18:42 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/06 21:18:42 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	des_b_src(char *d, const char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

static void	src_b_des(char *d, const char *s, size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		d[i - 1] = s[i - 1];
		i--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (!dest && !src)
		return (NULL);
	d = (char *)dest;
	s = (char *)src;
	if ((d == s) || (n == 0))
		return (dest);
	if (d < s)
		des_b_src(d, s, n);
	else
		src_b_des(d, s, n);
	return (dest);
}
