/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:05:01 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/06 18:21:52 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	exp_is_specifique_case(char *str, size_t idx)
{
	if (str[idx + 1] == '?' || str[idx + 1] == '$')
		return (1);
	return (0);
}

char	*exp_specifique_case_var(char *str, size_t *idx, int exit_status)
{
	*idx += 2;
	if (str[*idx - 1] == '?')
		return (ft_itoa(exit_status));
	if (str[*idx - 1] == '$')
		return (ft_strdup("$$"));
	return (NULL);
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

char	*exp_chr_var_and_exp(char *str, char **env, size_t *idx)
{
	char	*var;
	char	*expanded_var;
	size_t	i;

	var = exp_grab_var(str + *idx + 1);
	if (!var)
		return (NULL);
	if (!var[0])
	{
		free(var);
		*idx += 1;
		return (ft_strdup("$"));
	}
	*idx += 1 + ft_strlen(var);
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
	return (expanded_var);
}
