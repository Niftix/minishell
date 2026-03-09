/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 04:18:37 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/02/03 15:28:24 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol(const char *str)
{
	long long	res;
	int			i;
	int			sign;

	if (!str)
		return (0);
	sign = 1;
	res = 0;
	i = 0;
	while (((str[i] <= 13) && (str[i] >= 9)) || (str[i] == 32))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] <= '9' && (str[i] >= '0'))
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	return ((long)(res * sign));
}
