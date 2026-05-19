/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_verif_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:48:46 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/05/19 18:39:16 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	**exp_verif_expand(char **var, int *len_var, int pos, int *need_new)
{
	char	**tmp;
	int		tmp_len;
	size_t	old_len;
	size_t	new_len;

	if (exp_verif_if_space_without_q(var[pos]))
	{
		if (ft_strlen(var[pos]) && is_ifs(var[pos][ft_strlen(var[pos]) - 1]))
			*need_new = 1;
		tmp = exp_splited_var(var[pos]);
		if (!tmp)
			return (ft_free2c(var), NULL);
		tmp_len = ft_str2dlen(tmp);
		old_len = sizeof(char *) * *len_var;
		new_len = sizeof(char *) * (*len_var + tmp_len + 1);
		var = ft_realloc(var, old_len, new_len);
		free(var[pos]);
		var = exp_append_tmp_to_var(var, tmp, pos, need_new);
		*len_var += (tmp_len - 1);
	}
	return (var);
}
