/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:15:40 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/01/07 12:20:49 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_array(int *arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		ft_printf("| %d ", arr[i]);
	ft_printf("<-last\n");
}
