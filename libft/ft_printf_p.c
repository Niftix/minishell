/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:12:11 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/12/31 17:34:58 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_calc(unsigned long nb)
{
	int	len;

	len = 0;
	while (nb > 0)
	{
		len++;
		nb /= 16;
	}
	return (len);
}

int	ft_printf_p(unsigned long hex)
{
	t_var_printf_hex	var;

	if (!hex)
		return (ft_printf("(nil)"));
	ft_printf("0x");
	var.len = ft_len_calc(hex);
	var.res = malloc(sizeof(char) * (var.len + 1));
	if (!var.res)
		return (0);
	var.tab = "0123456789abcdef";
	var.res[var.len] = '\0';
	var.size = var.len;
	var.len--;
	while (hex > 0)
	{
		var.res[var.len] = var.tab[(hex % 16)];
		var.len--;
		hex /= 16;
	}
	ft_putstr_fd(var.res, 1);
	free(var.res);
	var.res = NULL;
	return (var.size + 2);
}
