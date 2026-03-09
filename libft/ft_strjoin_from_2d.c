/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_from_2d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:33:23 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/01/13 11:52:54 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_from_2d(char *s1, char **s2, size_t start)
{
	size_t	i;
	char	*res;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strdup(s1);
	if (!res)
		return (NULL);
	i = start;
	while (s2[i])
	{
		tmp = res;
		res = ft_strjoin(res, s2[i++]);
		free(tmp);
		if (!res)
			return (NULL);
	}
	return (res);
}
