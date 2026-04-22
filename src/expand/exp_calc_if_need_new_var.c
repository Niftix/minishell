/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_calc_if_need_new_var.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:32:47 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/22 14:35:01 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	exp_calc_if_need_new_var(char c, int need_new)
{
	if (need_new == 2)
		return (1);
	return (is_ifs(c));
}
