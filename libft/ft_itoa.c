/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:20:11 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/20 00:03:03 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(long int nb, int sign)
{
	int	len;

	len = 1;
	if (sign)
		len++;
	while (nb >= 10)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

static void	ft_write_digits(char *tab, long int nb, int len, int sign)
{
	int	i;

	i = len - 1;
	while (nb > 0)
	{
		tab[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (sign)
		tab[0] = '-';
}

char	*ft_itoa(int n)
{
	char		*tab;
	int			len;
	long int	nb;
	int			sign;

	nb = (long int)n;
	sign = 0;
	if (nb < 0)
	{
		sign = 1;
		nb = -nb;
	}
	len = ft_count_digits(nb, sign);
	tab = malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	if (nb == 0)
		tab[0] = '0';
	else
		ft_write_digits(tab, nb, len, sign);
	tab[len] = '\0';
	return (tab);
}
