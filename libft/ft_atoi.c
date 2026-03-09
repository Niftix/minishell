/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:18:14 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/06 21:18:14 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long	res;
	int		i;
	int		sign;

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
	return ((int)(res * sign));
}
