/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 23:30:36 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/01/12 20:57:32 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdupcat(char *dest, char *src, ssize_t *size, ssize_t add_size)
{
	char	*temp;
	ssize_t	i;
	ssize_t	j;

	if (dest)
	{
		temp = dest;
		dest = malloc(sizeof(char) * (*size + add_size + 1));
		if (!dest || !temp)
			return (NULL);
		i = -1;
		while (temp[++i])
			dest[i] = temp[i];
		j = -1;
		while (++j + i < *size + add_size)
			dest[i + j] = src[j];
		dest[i + j] = '\0';
		free(temp);
		temp = NULL;
	}
	else
		dest = ft_strdup(src);
	return (*size += add_size, dest);
}
