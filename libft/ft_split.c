/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:11:13 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/20 00:03:50 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cnt_w(const char *str, char c)
{
	int	i;
	int	in_w;
	int	cnt;

	cnt = 0;
	i = 0;
	in_w = 0;
	while (str[i])
	{
		if (str[i] == c)
			in_w = 0;
		else if (!in_w)
		{
			in_w = 1;
			cnt++;
		}
		i++;
	}
	return (cnt);
}

static char	*ft_dup_w(char const *s, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (i < end - start)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_free_all(char **tab, int last)
{
	int	i;

	i = 0;
	while (i < last)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	t_splitvar	var;

	if (!s)
		return (NULL);
	var.tab = malloc(sizeof(char *) * (ft_cnt_w(s, c) + 1));
	if (!var.tab)
		return (NULL);
	var.i = 0;
	var.j = 0;
	while (s[var.i])
	{
		while ((s[var.i] == c) && (s[var.i]))
			var.i++;
		var.start = var.i;
		while ((s[var.i] != c) && (s[var.i]))
			var.i++;
		if (var.start < var.i)
		{
			var.tab[var.j] = ft_dup_w(s, var.start, var.i);
			if (!var.tab[var.j++])
				return (ft_free_all(var.tab, var.j), NULL);
		}
	}
	return (var.tab[var.j] = NULL, var.tab);
}
