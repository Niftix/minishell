/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:28:33 by mville            #+#    #+#             */
/*   Updated: 2026/05/03 14:29:15 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "minishell.h"
#include <dirent.h>

char	**return_str(char *str)
{
	char	**res;

	res = malloc(sizeof(char *) * 2);
	if (!res)
		return (NULL);
	res[0] = ft_strdup(str);
	if (!res[0])
		return (free(res), NULL);
	res[1] = NULL;
	return (res);
}

char	**add_file(char **res, char *name)
{
	char	**new;
	int		len;

	len = 0;
	if (res)
		len = ft_str2dlen(res);
	new = ft_realloc(res, sizeof(char *) * (len + 1),
			sizeof(char *) * (len + 2));
	if (!new)
		return (ft_free_tab(res), NULL);
	new[len] = ft_strdup(name);
	if (!new[len])
		return (ft_free_tab(new), NULL);
	new[len + 1] = NULL;
	return (new);
}
