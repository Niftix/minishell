/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_verif_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:48:46 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/05/20 18:51:18 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	exp_verif_set_value(char **str, char *quote, size_t *i, int *r_len)
{
	*str = exp_skip_ifs(*str);
	*quote = 'x';
	*i = -1;
	*r_len = 1;
}

char	**exp_verif_expand(char **var, int *len_var, int pos, int *need_new)
{
	char	**tmp;
	int		tmp_len;
	size_t	old_len;
	size_t	new_len;

	if (!var)
		return (NULL);
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
		if (!var)
			return (NULL);
		free(var[pos]);
		var = exp_append_tmp_to_var(var, tmp, pos, need_new);
		*len_var += (tmp_len - 1);
	}
	return (var);
}
