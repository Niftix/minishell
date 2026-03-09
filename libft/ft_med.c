/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_med.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:47:59 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/01/07 12:14:52 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_med(int *stack, int size)
{
	int	*tmp_arr;
	int	median;
	int	i;

	tmp_arr = malloc(sizeof(int) * size);
	if (!tmp_arr)
		return (0);
	i = 0;
	while (i < size)
	{
		tmp_arr[i] = stack[i];
		i++;
	}
	ft_qsort(tmp_arr, 0, size - 1);
	median = tmp_arr[size / 2];
	free(tmp_arr);
	tmp_arr = NULL;
	return (median);
}
