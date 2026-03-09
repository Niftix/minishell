/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_stdin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 15:14:51 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/01/12 20:51:54 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_from_stdin(void)
{
	char	*line;
	char	*res;
	ssize_t	res_len;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	res_len = 0;
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		res = ft_strdupcat(res, line, &res_len, ft_strlen(line));
		free(line);
		if (!res)
			return (NULL);
	}
	return (res);
}
