/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var_append_without_new_idx.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:46:12 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/22 14:28:02 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	**exp_var_append_without_new_idx(char **res, int *r_len, char *var,
		int *need_new)
{
	res[*r_len - 2] = exp_var_append_to_last(res[*r_len - 2], var);
	if (!res[*r_len - 2])
		return (ft_free2c(res), NULL);
	res = exp_verif_expand(res, r_len, *r_len - 2, need_new);
	return (res);
}