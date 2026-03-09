/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:55:15 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/02/03 15:31:34 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strclen(const char *tab, const char c)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i] && tab[i] != c)
		i++;
	return (i);
}
