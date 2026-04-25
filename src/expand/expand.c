/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:57:54 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/24 22:48:22 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char	*exp_extract_var(char *str, char **env, size_t *idx,
			int exit_status)
{
	size_t		start;
	static int	in_v_quote = 0;
	char		quote;

	if (in_v_quote)
		return (in_v_quote = 0, exp_chose_var(str, env, idx, exit_status));
	quote = 'x';
	exp_set_exp_extract_var(&quote, str, idx);
	start = *idx;
	while (str[*idx])
	{
		if (quote == 'x' && (str[*idx] == '\'' || str[*idx] == '\"'))
			quote = str[*idx];
		else if (str[*idx] == quote)
			quote = 'x';
		if (str[*idx] == '$' && quote != '\'' && str[*idx + 1] != '"')
		{
			in_v_quote = str[*idx];
			return (exp_extract_none_var(str, start, *idx));
		}
		if (is_ifs(str[*idx]) && quote == 'x' && !in_v_quote)
			return (exp_extract_none_var(str, start, *idx));
		*idx += 1;
	}
	return (exp_extract_none_var(str, start, *idx));
}

char	*exp_var_append_to_last(char *dest, char *src)
{
	ssize_t	dest_len;

	if (!*src)
		return (dest);
	dest_len = ft_strlen(dest);
	dest = ft_strdupcat(dest, src, &dest_len, ft_strlen(src));
	return (dest);
}

static char	**exp_var_append(char **res, int *r_len, char *var, int *need_new)
{
	size_t	old_s;
	size_t	new_s;

	if (!*need_new && *r_len != 1)
		return (exp_var_append_without_new_idx(res, r_len, var, need_new));
	old_s = sizeof(char *) * (*r_len);
	new_s = sizeof(char *) * (*r_len + 1);
	res = ft_realloc(res, old_s, new_s);
	if (!res)
		return (free(var), NULL);
	res[*r_len - 1] = ft_strdup(var);
	if (!res[*r_len - 1])
		return (ft_free2c(res), NULL);
	res = exp_verif_expand(res, r_len, *r_len - 1, need_new);
	res[*r_len] = NULL;
	*r_len += 1;
	return (res);
}

static char	**exp_chr(char *str, char **env, size_t idx, int exit_status)
{
	char			*var;
	char			**res;
	int				r_len;
	static	int		need_new = 0;

	res = malloc(sizeof(char *) * 1);
	var = NULL;
	if (!res)
		return (NULL);
	r_len = 1;
	res[r_len - 1] = NULL;
	while (str[idx])
	{
		need_new = exp_calc_if_need_new_var(str[idx], need_new, str, idx);
		var = exp_extract_var(str, env, &idx, exit_status);
		if (!var)
			return (ft_free2c(res), need_new = 0, NULL);
		if (var[0] != '\0')
			res = exp_var_append(res, &r_len, var, &need_new);
		if (!res)
			return (ft_free2c(res), need_new = 0, NULL);
		free(var);
		var = NULL;
	}
	return (need_new = 0, res);
}

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
