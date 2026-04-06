/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:57:54 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/06 17:44:16 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_ifs(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static int	exp_is_var_sep(char c)
{
	if (c == '=')
		return (2); //no expand
	if (c == '$' || c == ';' || c == '"' || c == '\'' || c == '\\' || c == '}'
			|| c == ' ' || c == '\t' || c == '\n')
		return (1); //expand
	return (0); //continue
}

static char	*exp_grab_var(char *str)
{
	char	*var;
	size_t	var_len;
	size_t	idx;

	var_len = 0;
	while (str[var_len] && !exp_is_var_sep(str[var_len]))
		var_len++;
	if (str[var_len] == '}')
		var_len++;
	idx = 0;
	var = malloc(sizeof(char) * (var_len + 1));
	if (!var)
		return (NULL);
	var[var_len] = '\0';
	while (idx < var_len)
	{
		var[idx] = *str++;
		idx++;
	}
	return (var);
}

static char	*exp_chr_var_in_env(char **env, char *var)
{
	size_t	i;
	size_t	j;
	size_t	var_len;

	var_len = ft_strlen(var);
	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && var[j] && env[i][j] == var[j])
			j++;
		if (j == var_len && env[i][j] == '=')
			return (ft_strdup(env[i] + (j + 1)));
	}
	return (ft_strdup(""));
}

static char	*exp_chr_var_and_exp(char *str, char **env, size_t *idx)
{
	char	*var;
	char	*expanded_var;
	size_t	i;

	var = exp_grab_var(str + *idx + 1);
	if (!var)
		return (NULL);
	*idx += 1 +ft_strlen(var);
	if (str[*idx] == '}')
		*idx += 1;
	if (var[0] == '{')
	{
		i = -1;
		while (var[++i + 1] != '}')
			var[i] = var[i + 1];
		var[i] = '\0';
	}
	expanded_var = exp_chr_var_in_env(env, var);
	free(var);
	return(expanded_var);
}
static size_t	exp_skip_tab_space_nl(char *str, size_t start)
{
	size_t	idx;

	idx = start;
	while (str[idx] && (str[idx] == '\t' || str[idx] == ' '
			|| str[idx] == '\n'))
		idx++;
	return (idx);
}

static char	*exp_extract_none_var(char *str, size_t start, size_t end)
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

static int	exp_is_specifique_case(char *str, size_t idx)
{
	if (str[idx + 1] == '?' || str[idx + 1] == '$')
		return (1);
	return (0);
}

static char	*exp_specifique_case_var(char *str, size_t *idx, int exit_status)
{
	*idx += 2;
	if (str[*idx - 1] == '?')
		return (ft_itoa(exit_status));
	if (str[*idx - 1] == '$')
		return (ft_strdup("$$"));
	return (NULL);
}

static char *exp_extract_var(char *str, char **env, size_t *idx, char quote,
			int exit_status)
{
	size_t		start;
	static int	in_v = 0;

	if (in_v && exp_is_specifique_case(str, *idx))
		return (in_v = 0, exp_specifique_case_var(str, idx, exit_status));
	if (in_v)
			return(in_v = 0, exp_chr_var_and_exp(str, env, idx));
	if (quote == 'x')
			*idx = exp_skip_tab_space_nl(str, *idx);
	start = *idx;
	while (str[*idx])
	{
		if (quote == 'x' && (str[*idx] == '\'' || str[*idx] == '\"'))
			quote = str[*idx];
		else if (str[*idx] == quote)
			quote = 'x';
		if (str[*idx] == '$' && quote != '\'')
		{
			in_v = 1;
			return (exp_extract_none_var(str, start, *idx));
		}
		if (is_ifs(str[*idx]) && quote == 'x' && !in_v)
			return (exp_extract_none_var(str, start, *idx));
		*idx += 1;
	}
	return (exp_extract_none_var(str, start, *idx));
}

static char	*exp_var_append_to_last(char *dest, char *src)
{
	ssize_t	dest_len;

	if (!*src)
		return (dest);
	dest_len = ft_strlen(dest);
	dest = ft_strdupcat(dest, src, &dest_len, ft_strlen(src));
	return (dest);
}

static char	**exp_var_append(char **res, int *r_len, char *var, int need_new)
{
	size_t	old_s;
	size_t	new_s;

	if (!need_new && *r_len != 1)
	{
		res[*r_len - 2] = exp_var_append_to_last(res[*r_len - 2], var);
		free(var);
		if (!res[*r_len - 2])
			return (ft_free2c(res), NULL);
		return (res);
	}
	old_s = sizeof(char *) * (*r_len);
	new_s = sizeof(char *) * (*r_len + 1);
	res = ft_realloc(res, old_s, new_s);
	if (!res)
		return (free(var), NULL);
	res[*r_len - 1] = ft_strdup(var);
	free(var);
	if (!res[*r_len - 1])
		return (ft_free2c(res), NULL);
	res[*r_len] = NULL;
	*r_len += 1;
	return (res);
}

static char	**exp_chr(char *str, char **env, size_t idx, char quote,
			int exit_status)
{
	char	*var;
	char	**res;
	int		r_len;
	int		ifs;

	res = malloc(sizeof(char *) * 1);
	var = NULL;
	if (!res)
		return (NULL);
	r_len = 1;
	res[r_len - 1] = NULL;
	while (str[idx])
	{                
		ifs = is_ifs(str[idx]);
		var = exp_extract_var(str, env, &idx, quote, exit_status);
		if (!var)
			return (ft_free2c(res), NULL);
		res = exp_var_append(res, &r_len, var, ifs);	//continue to handle all var
		if (!res)
			return (ft_free2c(res), NULL);
		var = NULL;
	}
	return (res);
}

char	**expand(char *str, char **env, int	exit_status)
{
	char	quote;
	size_t	idx;
	char	**res;

	if (!str)
		return (NULL);
	idx = 0;
	quote = 'x';
	res = exp_chr(str, env, idx, quote, exit_status);
	free(str);
	return (res);
}
