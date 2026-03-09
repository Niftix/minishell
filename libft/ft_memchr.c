/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:18:37 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/06 21:18:37 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *mem, int chr, size_t size)
{
	const unsigned char	*ptr;
	unsigned char		target;

	ptr = (const unsigned char *)mem;
	target = (unsigned char)chr;
	while (size--)
	{
		if (*ptr == target)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
