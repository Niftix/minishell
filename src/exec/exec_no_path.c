/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:34:35 by mville            #+#    #+#             */
/*   Updated: 2026/05/20 18:59:18 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char	*resolve_without_path(char *cmd)
{
	char	*tmp;

	tmp = build_full_path(".", cmd);
	if (!tmp)
		return (NULL);
	if (access(tmp, X_OK) == 0 && !check_if_directory(tmp))
		return (tmp);
	free(tmp);
	return (NULL);
}
