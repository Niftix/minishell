/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:57:54 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/03 18:47:51 by vcucuiet         ###   ########.fr       */
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

static char	*exp_exchange_var(char *str, char *var, char *new_var, ssize_t *idx)
{
	ssize_t	old_v_len;
	ssize_t	new_v_len;
	char	*remain;
	ssize_t	i;

	old_v_len = ft_strlen(var);
	new_v_len = ft_strlen(new_var);
	remain = ft_strdup(str + (*idx + old_v_len + 1));
	if (!remain)
		return (free(str), NULL);
	i = 0;
	while (i < new_v_len)
	{
		str[*idx] = new_var[i++];
		*idx += 1;
	}
	i = -1;
	while (remain[++i])
		str[*idx + i] = remain[i];
	str[*idx + i] = '\0';
	free(remain);
	return (str);
}

static char	*exp_merge_var_to_str(char *str, char **env, char *var, ssize_t *idx)
{
	size_t	old_size;
	size_t	new_size;
	char	*new_var;

	new_var = exp_chr_var_in_env(env, var);
	if (!new_var)
		return (NULL);//malloc error
	old_size = ft_strlen(str);
	new_size = old_size + (ft_strlen(new_var) - ft_strlen(var));
	if (new_size > old_size)
	{
		str = ft_realloc(str, old_size, new_size);
		if (!str)
			return (NULL);//malloc error
	}
	str = exp_exchange_var(str, var, new_var, idx);
	if (!str)
		return (NULL);//malloc error
	free(new_var);
	if (new_size < old_size)
		str = ft_realloc(str, old_size, new_size);
	return (str);
}

static char	*exp_chr(char *str, char **env, ssize_t idx, char quote, char *var)
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
			str = exp_merge_var_to_str(str, env, var, &idx);
			free(var);
			var = NULL;
			if (!str)
				return (NULL); //malloc error
		}
		else
			idx++;
	}
	return (str);
}

char	**exp_specifique_case(int state)
{
	char	**res;
	if (state == 1)
	{
		res = malloc(sizeof(char *) * 2);
		if (!res)
			return (NULL);
		res [0] = ft_strdup("");
		if (!res[0])
			return (free(res), NULL);
		res[1] = NULL;
		return (res);
	}
	return (NULL);
}

char	**expand(char *str, char **env)
{
	char	quote;
	char	*var;
	ssize_t	idx;
	char	**res;

	if (!str)
		return (NULL);
	idx = 0;
	quote = 'x';
	var = NULL;
	str = exp_chr(str, env, idx, quote, var);
	if (!str)
		return (NULL); // malloc error
	if (str[0] == '\0')
		res = exp_specifique_case(1);
	else
		res = ft_split(str, ' ');
	free(str);
	return (res);
}
