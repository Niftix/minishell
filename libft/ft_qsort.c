/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:58:09 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/02/03 15:30:40 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	partitioning(int *arr, int low, int high)
{
	int	to_swap;
	int	i;
	int	j;

	to_swap = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] <= to_swap)
		{
			i++;
			ft_swap(&arr[i], &arr[j]);
		}
		j++;
	}
	ft_swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	ft_qsort(int *arr, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = partitioning(arr, low, high);
		ft_qsort(arr, low, pivot - 1);
		ft_qsort(arr, pivot + 1, high);
	}
}
