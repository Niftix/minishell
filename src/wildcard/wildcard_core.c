/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 12:34:55 by mville            #+#    #+#             */
/*   Updated: 2026/05/03 21:33:30 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "minishell.h"
#include <dirent.h>

int	wildcard_checker(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else if (str[i] == '*' && !quote)
			return (1);
		i++;
	}
	return (0);
}


static int	skip_usless_file(char *pattern, char *filename)
{
	if (ft_strcmp(filename, ".") == 0 || ft_strcmp(filename, "..") == 0)
		return (1);
	if (filename[0] == '.' && pattern[0] != '.')
		return (1);
	return (0);
}

static int	add_match(char ***res, char *pattern, char *filename)
{
	if (skip_usless_file(pattern, filename))
		return (0);
	if (!find_match(pattern, filename))
		return (0);
	*res = add_file(*res, filename);
	if (!*res)
		return (1);
	return (0);
}

char	**wildcard_core(char *str)
{
	char			**res;
	DIR				*dir;
	struct dirent	*file;

	if (wildcard_checker(str) == 0)
		return (return_str(str));
	dir = opendir(".");
	if (!dir)
		return (return_str(str));
	res = NULL;
	file = readdir(dir);
	while (file)
	{
		if (add_match(&res, str, file->d_name))
			return (closedir(dir), NULL);
		file = readdir(dir);
	}
	closedir(dir);
	if (!res)
		return (return_str(str));
	return (res);
}
