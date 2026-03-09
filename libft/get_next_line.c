/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:43:53 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/12/31 17:06:25 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_remain(char *str, int status, char **stash, t_var_gnl val)
{
	int	j;

	if (status == 1)
	{
		j = -1;
		while ((*stash)[++j] && ((*stash)[j] != '\n'))
			str[j] = (*stash)[j];
		if ((*stash)[j] == '\n')
			str[j++] = '\n';
		str[j] = '\0';
		if (str[0] == '\0')
			str = NULL;
		if ((*stash)[j] == '\0')
		{
			free(*stash);
			*stash = NULL;
			return ;
		}
		val.temp = *stash;
		*stash = ft_strdup(*stash + j);
		free(val.temp);
		val.temp = NULL;
	}
	else if (status == 2)
		*stash = ft_strdup(str);
}

static char	*get_n(char *buf, ssize_t c_buf)
{
	ssize_t	i;
	char	*tab;

	tab = malloc(sizeof(char) * (c_buf + 1));
	i = 0;
	while (i < c_buf)
	{
		tab[i] = buf[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

static void	ft_diff_cbuf_read(t_var_gnl *val, char **stash)
{
	get_remain(val->buf + val->c_buf + 1, 2, stash, *val);
	val->temp = get_n(val->buf, val->c_buf + 1);
	val->res = ft_strdupcat(val->res, val->temp, &val->t_size, val->c_buf + 1);
	if (val->res[0] == '\0')
	{
		if (*stash)
			free(*stash);
		*stash = NULL;
		val->res = NULL;
	}
}

static char	*get_str(int fd, t_var_gnl *val, char **stash)
{
	while (1)
	{
		val->t_read = read(fd, val->buf, BUFFER_SIZE);
		if (val->t_read > 0)
		{
			val->buf[val->t_read] = '\0';
			val->c_buf = 0;
			while (val->buf[val->c_buf] && (val->buf[val->c_buf] != '\n'))
				val->c_buf += 1;
			if (val->buf[val->c_buf] == '\n')
			{
				ft_diff_cbuf_read(val, stash);
				free(val->temp);
				val->temp = NULL;
				break ;
			}
			else
				val->res = ft_strdupcat(val->res,
						val->buf, &val->t_size, val->t_read);
		}
		if (ft_gnl_check_break(val, 0))
			break ;
	}
	ft_gnl_check_break(val, -1);
	return (val->res);
}

char	*get_next_line(int fd)
{
	t_var_gnl	val;
	static char	*stashs[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	ft_set_gnl_to_default(&val, &stashs[fd], 0);
	if (!val.buf)
		return (NULL);
	if (stashs[fd] != NULL)
	{
		val.c_buf = 0;
		get_remain(val.buf, 1, &stashs[fd], val);
		val.res = ft_strdupcat(val.res,
				val.buf, &val.t_size, ft_strlen(val.buf));
		while (val.buf[val.c_buf] && (val.buf[val.c_buf] != '\n'))
			val.c_buf += 1;
		if (val.res[val.c_buf] == '\n')
			return (ft_gnl_check_break(&val, 1), val.res);
	}
	val.res = get_str(fd, &val, &stashs[fd]);
	ft_gnl_check_break(&val, 1);
	ft_set_gnl_to_default(&val, &stashs[fd], 1);
	return (val.res);
}
