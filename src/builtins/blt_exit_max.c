/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:40:54 by mville            #+#    #+#             */
/*   Updated: 2026/04/16 21:51:31 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_exit_num_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}

int	blt_exit_parse_status(char *str)
{
	unsigned long long	nb;
	unsigned long long	limit;
	int					sign;

	nb = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	limit = LLONG_MAX + (sign == -1);
	while (*str)
	{
		if (nb > limit / 10 || (nb == limit / 10
				&& (unsigned long long)(*str - '0') > limit % 10))
			return (256);
		nb = nb * 10 + (*str - '0');
		str++;
	}
	if (sign == -1)
		return ((unsigned char)(-(long long)nb));
	return ((unsigned char)((long long)nb));
}
