/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:18:19 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/06 21:18:19 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t e_cnt, size_t e_size)
{
	void	*ptr;
	size_t	total;
	size_t	i;

	total = e_cnt * e_size;
	if ((e_cnt > 0) && (total / e_cnt != e_size))
		return (NULL);
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < total)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
