/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_stash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 14:27:17 by mville            #+#    #+#             */
/*   Updated: 2026/04/24 19:58:51 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_stash(t_input_stash *input_stash)
{
	free(input_stash->stash);
	input_stash->stash = NULL;
	input_stash->idx = 0;
}

static char	*add_to_stash(t_input_stash *input_stash)
{
	char	*stash;
	char	*line;
	size_t	i;
	size_t	start;

	stash = input_stash->stash;
	start = input_stash->idx;
	i = start;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_substr(stash, start, i - start);
	if (!line)
		return (clean_stash(input_stash), NULL);
	if (stash[i] == '\n')
		i++;
	input_stash->idx = i;
	if (!stash[i])
		clean_stash(input_stash);
	return (line);
}

char	*get_stash_line(t_input_stash *input_stash)
{
	if (!input_stash->stash)
		return (NULL);
	return (add_to_stash(input_stash));
}

char	*check_multi_line(t_input_stash *input_stash, char *input)
{
	if (!input || !ft_strchr(input, '\n'))
		return (input);
	input_stash->stash = input;
	input_stash->idx = 0;
	return (add_to_stash(input_stash));
}
