/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:29:38 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/05/19 18:38:06 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	**expand(char *str, char **env, int exit_status)
{
	size_t	idx;
	char	**res;

	if (!str)
		return (NULL);
	str = exp_cringe_dolars(str);
	idx = 0;
	res = exp_chr(str, env, idx, exit_status);
	free(str);
	return (res);
}
