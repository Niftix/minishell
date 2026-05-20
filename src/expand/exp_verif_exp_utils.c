/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_verif_exp_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:35:35 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/05/20 18:52:10 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	exp_verif_if_space_without_q(char *str)
{
	size_t	i;
	char	quote;

	if (!str)
		return (0);
	quote = 'x';
	i = -1;
	while (str[++i])
	{
		if ((str[i] == 34 || str[i] == 39) && quote == 'x')
			quote = str[i];
		else if (str[i] == quote)
			quote = 'x';
		if ((str[i] == ' ' || str[i] == '\t') && quote == 'x')
			return (1);
	}
	return (0);
}

char	**exp_append_new_str(char **res, char *str, size_t *i, int *r_len)
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

char	*exp_skip_ifs(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && is_ifs(str[i]))
		i++;
	if (i > 0)
		str = ft_memmove(str, str + i, ft_strlen(str + i) + 1);
	return (str);
}

char	**exp_splited_var(char *str)
{
	size_t	i;
	int		r_len;
	char	quote;
	char	**res;

	exp_verif_set_value(&str, &quote, &i, &r_len);
	res = malloc(sizeof(char *) * r_len);
	if (!res)
		return (NULL);
	res[r_len - 1] = NULL;
	while (str[++i])
	{
		if ((str[i] == 39 || str[i] == 34) && quote == 'x')
			quote = str[i];
		else if (str[i] == quote)
			quote = 'x';
		if ((str[i] == ' ' || str[i] == '\t') && quote == 'x')
			res = exp_append_new_str(res, str, &i, &r_len);
		if (!res)
			return (NULL);
	}
	if (i)
		res = exp_append_new_str(res, str, &i, &r_len);
	return (res);
}

char	**exp_append_tmp_to_var(char **var, char **tmp, int pos,
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
