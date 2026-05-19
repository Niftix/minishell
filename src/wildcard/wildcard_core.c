/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 12:34:55 by mville            #+#    #+#             */
/*   Updated: 2026/05/19 23:07:31 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "minishell.h"
#include <dirent.h>

static char	*remove_quote(char *str)
{
	char	*new;
	char	quote;
	int		i;
	int		j;

	new = malloc(ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	quote = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!quote && (str[i] == 39 || str[i] == 34))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

int	wildcard_checker(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == 39 || str[i] == 34))
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
	char	*clean_pattern;
	int		match;

	if (skip_usless_file(pattern, filename))
		return (0);
	clean_pattern = remove_quote(pattern);
	if (!clean_pattern)
		return (1);
	match = find_match(clean_pattern, filename);
	free(clean_pattern);
	if (!match)
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

	if (!wildcard_checker(str))
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
