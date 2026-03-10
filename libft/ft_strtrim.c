/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:45:10 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/21 09:07:50 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inset(char const c, char const *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*res;

	if (!s1)
		return (NULL);
	while (*s1 && inset(*s1, set))
		s1++;
	len = ft_strlen(s1);
	while (len > 0 && inset(s1[len - 1], set))
		len--;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (len)
	{
		while (len > 0)
		{
			res[len - 1] = s1[len - 1];
			len--;
		}
	}
	return (res);
}
