/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:57:54 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/30 23:50:34 by vcucuiet         ###   ########.fr       */
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

static int	exp_cnt_var(char *str)
{
    int i = 0;
    while (*str)
    {
        if (*str == '$')
            i++;
        str++;
    }
    return (i);
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
		var[idx] = str[idx];
		idx++;
	}
	return (var);
}

static size_t	exp_merge_var_to_str(char *str, char *var, size_t idx)
{
	size_t	new_idx;

	new_idx = idx;
	//NEXT STEP
	free(var);
	var = NULL;
	return (new_idx);
}

char	*expand(char *str, char	**env)
{
	int		nb_var;
	char	quote;
	char	*var;
	size_t	idx;

	if (!str)
		return (NULL);
	nb_var = exp_cnt_var(str);
	if  (nb_var == 0)
		return (str);
	idx = 0;
	quote = 'x';
	var = NULL;
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
			idx = exp_merge_var_to_str(str, var, idx);
		idx++;
	}
	return (str);
}
