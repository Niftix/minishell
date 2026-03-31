/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:57:54 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/31 14:25:48 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	idx = 0;
	var = malloc(sizeof(char) * (var_len + 1));
	if (!var)
		return (NULL);
	var[var_len] = '\0';
	while (idx < var_len)
	{
		var[idx] = *str;
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

static char	exp_exchange_var(char *str, char var, char *new_var, size_t *idx)
{
	size_t	old_v_len;
	size_t	new_v_len;
	char	*remain;

	old_v_len = ft_strlen(var);
	new_v_len = ft_strlen(new_var);
	remain = ft_strdup(str + (*idx + old_v_len + 1));
	if (!remain)
		return (free(str), NULL);
	while (new_var)
	
}

static size_t	exp_merge_var_to_str(char *str, char **env, char *var, size_t idx)
{
	size_t	new_idx;
	size_t	old_size;
	size_t	new_size;
	char	*new_var;

	new_idx = idx;
	new_var = exp_chr_var_in_env(env, var);
	if (!new_var)
		return (NULL);//malloc error
	old_size = ft_strlen(str);
	new_size = old_size + ft_strlen(new_var) - ft_strlen(var) + 1;
	if (new_size > old_size)
	{
		str = ft_realloc(str, old_size, new_size);
		if (!str)
			return (NULL);//malloc error
	}
	str = exp_exchange_var(str, var, new_var, &new_idx);
	if (!str)
		return (NULL);//malloc error
	free(var);
	var = NULL;
	if (new_size < old_size)
		str = ft_realloc(str, old_size, new_size);
	return (new_idx);
}

static char	*exp_chr(char *str, char **env, int idx, char quote, char *var)
{
	while (str[idx])
	{
		if (quote == 'x' && (str[idx] == '\'' || str[idx] == '\"'))
			quote = str[idx];
		else if (str[idx] == quote)
			quote = 'x';
		if (str[idx] == '$' && quote != '\'')
		{
			var = exp_grab_var(str + idx + 1);
			if (!var)
				return (NULL); //malloc error
		}
		if (var)
		{
			idx = exp_merge_var_to_str(str, env, var, idx);
			if (!var)
				return (NULL); // malloc error
		}
		idx++;
	}
}
char	**expand(char *str, char	**env)
{
	char	quote;
	char	*var;
	size_t	idx;

	if (!str)
		return (NULL);
	idx = 0;
	quote = 'x';
	var = NULL;
	str = exp_chr(str, env, idx, quote, var);
	if (!str)
		return (NULL); // malloc error
	return (str);
}
