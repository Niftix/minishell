/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:11:41 by mville            #+#    #+#             */
/*   Updated: 2026/04/13 23:01:16 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd_env(t_shell *shell)
{
	char	pwd_result[PATH_MAX];

	if (!getcwd(pwd_result, PATH_MAX))
		return (1);
	return (update_env(shell, pwd_result));
}

int	blt_cd(t_shell *shell, t_ast *ast)
{
	char	*path;

	path = ast->args_cmd[1];
	if (!path)
		return (0);
	if (ast->args_cmd[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (update_pwd_env(shell));
}
