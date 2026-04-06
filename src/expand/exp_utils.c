/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:13:05 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/06 18:41:46 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	is_ifs(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	exp_is_var_sep(char c)
{
	if (c == '$' || c == ';' || c == '"' || c == '\'' || c == '\\' || c == '}'
		|| c == ' ' || c == '\t' || c == '\n' || c == '=')
		return (1);
	return (0);
}

size_t	exp_skip_tab_space_nl(char *str, size_t start)
{
	size_t	idx;

	idx = start;
	while (str[idx] && (str[idx] == '\t' || str[idx] == ' '
			|| str[idx] == '\n'))
		idx++;
	return (idx);
}

char	*exp_chose_var(char *str, char **env, size_t *idx, int exit_status)
{
	if (exp_is_specifique_case(str, *idx))
		return (exp_specifique_case_var(str, idx, exit_status));
	return (exp_chr_var_and_exp(str, env, idx));
}
