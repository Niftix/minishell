/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccnt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:03:03 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/02/03 15:31:02 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strccnt(char *str, char c)
{
	int		cnt;
	ssize_t	i;

	if (!str)
		return (0);
	i = -1;
	cnt = 0;
	while (str[++i])
	{
		if (str[i] == c)
			cnt++;
	}
	return (cnt);
}
