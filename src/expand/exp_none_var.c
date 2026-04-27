/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_none_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:06:48 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/17 14:05:38 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*exp_extract_none_var(char *str, size_t start, size_t end)
{
	char	*var;
	size_t	i;
	size_t	len;

	len = end - start;
	var = malloc(sizeof(char) * (len + 1));
	if (!var)
		return (var);
	var[len] = '\0';
	i = 0;
	while (i < len)
		var[i++] = str[start++];
	return (var);
}
