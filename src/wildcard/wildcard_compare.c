/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_compare.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 13:15:11 by mville            #+#    #+#             */
/*   Updated: 2026/05/03 21:32:20 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "minishell.h"
#include <dirent.h>

static void	return_to_last_star(t_wildcard *wild)
{
	wild->i_pattern = wild->last_star + 1;
	wild->save_file++;
	wild->i_file = wild->save_file;
}

static int	check_end_pattern(char *pattern, int i)
{
	while (pattern[i] == '*')
		i++;
	if (pattern[i] == '\0')
		return (1);
	return (0);
}

static	void	init_struct(t_wildcard *wild)
{
	wild->i_pattern = 0;
	wild->i_file = 0;
	wild->last_star = -1;
	wild->save_file = -1;
}

int	find_match(char *pattern, char *filename)
{
	t_wildcard	wild;

	init_struct(&wild);
	while (filename[wild.i_file])
	{
		if (pattern[wild.i_pattern] == filename[wild.i_file])
		{
			wild.i_pattern++;
			wild.i_file++;
		}
		else if (pattern[wild.i_pattern] == '*')
		{
			wild.last_star = wild.i_pattern;
			wild.save_file = wild.i_file;
			wild.i_pattern++;
		}
		else if (wild.last_star != -1)
			return_to_last_star(&wild);
		else
			return (0);
	}
	return (check_end_pattern(pattern, wild.i_pattern));
}
