/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/11/06 21:19:09 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/06 21:19:09 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	j;

	if (!dest || !src)
		return (0);
	srclen = ft_strlen(src);
	if (!size)
		return (srclen);
	destlen = ft_strlen(dest);
	j = 0;
	while ((destlen + j < size - 1) && (src[j]))
	{
		dest[destlen + j] = src[j];
		j++;
	}
	dest[destlen + j] = '\0';
	if (destlen >= size)
		return (size + srclen);
	return (destlen + srclen);
}
