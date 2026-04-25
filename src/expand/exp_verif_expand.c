/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_verif_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:48:46 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/24 21:49:02 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int		exp_verif_if_space_without_q(char *str)
{
	size_t	i;
	char	quote;

	if (!str)
		return (0);
	quote = 'x';
	i = -1;
	while (str[++i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && quote == 'x')
			quote = str[i];
		else if (str[i] == quote)
			quote = 'x';
		if (str[i] == ' ' && quote == 'x')
			return (1);
	}
	return (0);
}

static char	**exp_append_new_str(char **res, char *str, size_t *i, int *r_len)
{
	size_t	old_s;
	size_t	new_s;

	old_s = sizeof(char *) * (*r_len);
	new_s = sizeof(char *) * (*r_len + 1);
	res = ft_realloc(res, old_s, new_s);
	if (!res)
		return (NULL);
	res[*r_len - 1] = exp_extract_none_var(str, 0, *i);
	if (!res[*r_len - 1])
		return (ft_free2c(res), NULL);
	res[*r_len] = NULL;
	*r_len += 1;
	*i = exp_skip_tab_space_nl(str, *i);
	str = ft_memmove(str, str + *i, ft_strlen(str + *i) + 1);
	*i = -1;
	return (res);
}

static char	**exp_splited_var(char *str)
{
	size_t	i;
	int		r_len;
	char	quote;
	char	**res;

	quote = 'x';
	i = -1;
	r_len = 1;
	res = malloc(sizeof(char *) * r_len);
	res[r_len - 1] = NULL;
	while(str[++i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && quote == 'x')
            quote = str[i];
        else if (str[i] == quote)
            quote = 'x';
		if (str[i] == ' ' && quote == 'x')
			res = exp_append_new_str(res, str, &i, &r_len);
	}
	if (i)
		res = exp_append_new_str(res, str, &i, &r_len);
	return (res);
}

static char	**exp_append_tmp_to_var(char **var, char **tmp, int pos,
		 int *need_new)
{
	int		tmp_len;
	int		idx;

	idx = -1;
	if (!*need_new && var[0])
	{
		var[pos] = tmp[0];
		if (!var[pos])
			return (ft_free2c(var), NULL);
		idx++;
	}
	tmp_len = ft_str2dlen(tmp);
	while (++idx < tmp_len)
		var[pos + idx] = tmp[idx];
	var[pos + idx] = NULL;
	free(tmp);
	return (var);
}

char	** exp_verif_expand(char **var, int *len_var, int pos, int *need_new)
{
	char	**tmp;
	int		tmp_len;
	size_t	old_len;
	size_t	new_len;

	if (exp_verif_if_space_without_q(var[pos]))
	{
		if (ft_strlen(var[pos]) && is_ifs(var[pos][ft_strlen(var[pos]) - 1]))
			*need_new = 2;
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
