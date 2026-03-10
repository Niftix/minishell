/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:07:16 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/12/31 17:34:49 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_case(char *str, char c)
{
	int	i;

	i = -1;
	if (c == 'x')
	{
		while (str[++i])
			str[i] = ft_tolower(str[i]);
	}
}

static int	ft_len_calc(unsigned int nb)
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

int	ft_printf_hex(unsigned int hex, char c)
{
	t_var_printf_hex	var;

	if (!hex)
		return (write(1, "0", 1));
	var.len = ft_len_calc(hex);
	var.res = malloc(sizeof(char) * (var.len + 1));
	if (!var.res)
		return (0);
	var.tab = "0123456789ABCDEF";
	var.res[var.len] = '\0';
	var.size = var.len;
	var.len--;
	while (hex > 0)
	{
		var.res[var.len] = var.tab[(hex % 16)];
		var.len--;
		hex /= 16;
	}
	ft_case(var.res, c);
	ft_putstr_fd(var.res, 1);
	free(var.res);
	var.res = NULL;
	return (var.size);
}
