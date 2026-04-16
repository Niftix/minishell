/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 18:13:42 by mville            #+#    #+#             */
/*   Updated: 2026/04/13 23:01:22 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_pwd(void)
{
	char	pwd_result[PATH_MAX];

	if (!getcwd(pwd_result, PATH_MAX))
		return (1);
	ft_putstr_fd(pwd_result, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
