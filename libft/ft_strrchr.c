/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:19:23 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/06 21:19:23 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*res;
	char	chr;

	if (!str)
		return (0);
	res = NULL;
	chr = (char)c;
	while (1)
	{
		if (*str == chr)
			res = (char *)str;
		if (*str == '\0')
			break ;
		str++;
	}
	return (res);
}
