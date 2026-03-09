/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:18:45 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/06 21:18:45 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int val, size_t cnt)
{
	char	*d;
	size_t	i;

	d = (char *)ptr;
	i = 0;
	while (i < cnt)
	{
		d[i] = val;
		i++;
	}
	return (ptr);
}
