/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:02:28 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/02/03 15:27:51 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_val(char c, char c_case)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f' && c_case >= 'a' && c_case < 'z')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F' && c_case >= 'A' && c_case < 'Z')
		return (c - 'A' + 10);
	return (-1);
}

int	ft_atoi_hex(char *str)
{
	int		res;
	int		val;
	char	c;

	if (!str)
		return (0);
	res = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
	{
		str += 2;
		c = str[1];
	}
	while (*str)
	{
		val = get_val(*str, c);
		if (val == -1)
			break ;
		res = res * 16 + val;
		str++;
	}
	return (res);
}
