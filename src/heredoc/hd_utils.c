/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:31:23 by mville            #+#    #+#             */
/*   Updated: 2026/05/20 18:58:45 by vcucuiet         ###   ########.fr       */
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
	size_t	j;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	j = 0;
	while (line[j])
	{
		if (line[j] == '$')
			str = exp_chose_var(line, shell->env, &j, shell->status_exit);
		else
		{
			str = exp_extract_none_var(line, j, j + 1);
			j++;
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

void	put_hd_none_line_error(char *name)
{
	ft_putstr_fd("minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted '", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("')\n", 2);
}
