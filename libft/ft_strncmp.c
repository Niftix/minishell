/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:19:19 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/06 21:19:19 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	size_t			i;
	unsigned char	*first;
	unsigned char	*sec;

	if (!s1 || !s2)
		return (0);
	first = (unsigned char *)s1;
	sec = (unsigned char *)s2;
	i = 0;
	while (first[i] && sec[i] && (i < len))
	{
		if (first[i] != sec[i])
			break ;
		i++;
	}
	if (i == len)
		return (0);
	else if (first[i] - sec[i] > 0)
		return (1);
	else if (first[i] - sec[i] < 0)
		return (-1);
	return (0);
}
