/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_add1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:02:26 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/12/31 17:34:40 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_c(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_printf_s(char *str)
{
	if (!str)
		return (ft_putstr_fd("(null)", 1), 6);
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_printf_d_i(int n)
{
	char	*nb;
	int		size;

	nb = ft_itoa(n);
	ft_putstr_fd(nb, 1);
	size = ft_strlen(nb);
	free(nb);
	return (size);
}

int	ft_printf_u(unsigned int n)
{
	t_var_printf_u	var;

	if (!n)
		return (write(1, "0", 1));
	var.len = 0;
	var.nb = n;
	while (var.nb > 0)
	{
		var.len++;
		var.nb /= 10;
	}
	var.tab = malloc(sizeof(char) * (var.len + 1));
	if (!var.tab)
		return (0);
	var.tab[var.len] = '\0';
	var.size = var.len;
	while (n > 0)
	{
		var.tab[--var.len] = (n % 10) + '0';
		n /= 10;
	}
	ft_putstr_fd(var.tab, 1);
	free(var.tab);
	var.tab = NULL;
	return (var.size);
}
