/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:31:23 by mville            #+#    #+#             */
/*   Updated: 2026/04/28 13:44:24 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*remove_quote(char *str)
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
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
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

char	*add_res(char *res, char *str)
{
	char	*new;

	new = ft_strjoin(res, str);
	free(res);
	free(str);
	return (new);
}

static char	*expand_line(char *line, t_shell *shell)
{
	char	*res;
	char	*str;
	size_t	idx;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	idx = 0;
	while (line[idx])
	{
		if (line[idx] == '$')
			str = exp_chose_var(line, shell->env, &idx, shell->status_exit);
		else
		{
			str = exp_extract_none_var(line, idx, idx + 1);
			idx++;
		}
		if (!str)
			return (free(res), NULL);
		res = add_res(res, str);
		if (!res)
			return (NULL);
	}
	return (res);
}

int	write_line_hd(t_redirect *redir, t_shell *shell, char *line, int exp)
{
	char	*new;

	if (exp)
	{
		new = expand_line(line, shell);
		free(line);
		if (!new)
			return (1);
		line = new;
	}
	ft_putstr_fd(line, redir->fd);
	ft_putstr_fd("\n", redir->fd);
	free(line);
	return (0);
}

int	close_hd(t_redirect *redir, char *name)
{
	close(redir->fd);
	redir->fd = open(name, O_RDONLY);
	unlink(name);
	free(name);
	return (0);
}
