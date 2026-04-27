/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_calc_if_need_new_var.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:32:47 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/26 15:10:12 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"



int	exp_calc_if_need_new_var(char c, int need_new, char *str, size_t idx)
{
	int	new;

	if (need_new > 1)
		return (need_new - 1);
	new = is_ifs(c);
	if (exp_get_quote_state(str, idx) != 'x')
		new = 0;
	return (new);
}
