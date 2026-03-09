/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 09:42:40 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/12/31 17:35:13 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c)
{
	char	*set;
	int		i;

	i = 0;
	set = "%csdiuxXp";
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_params(char c, va_list arg)
{
	int	size;

	size = 0;
	if (c == 'c')
		size += ft_printf_c(va_arg(arg, int));
	else if (c == 's')
		size += ft_printf_s(va_arg(arg, char *));
	else if (c == 'd' || c == 'i')
		size += ft_printf_d_i(va_arg(arg, int));
	else if (c == 'u')
		size += ft_printf_u(va_arg(arg, unsigned int));
	else if (c == 'x' || c == 'X')
		size += ft_printf_hex(va_arg(arg, unsigned long), c);
	else if (c == 'p')
		size += ft_printf_p(va_arg(arg, unsigned long));
	else if (c == '%')
		size += ft_printf_c('%');
	return (size);
}

void	set_to_0(int *i, int *size)
{
	*i = 0;
	*size = 0;
}

int	ft_printf(const char *str, ...)
{
	t_var_printf_val	var;

	if (!str)
		return (-1);
	set_to_0(&var.i, &var.size);
	va_start(var.arg, str);
	while (str[var.i])
	{
		if (str[var.i] == '%')
		{
			if (in_set(str[var.i + 1]))
				var.size += ft_params(str[var.i + 1], var.arg);
			else
				var.i -= 2;
			var.i += 2;
		}
		else
		{
			ft_putchar_fd(str[var.i++], 1);
			var.size++;
		}
		if (!str[var.i])
			return (va_end(var.arg), var.size);
	}
	return (va_end(var.arg), var.size);
}
