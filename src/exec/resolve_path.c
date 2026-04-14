/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 19:12:06 by mville            #+#    #+#             */
/*   Updated: 2026/04/14 17:27:49 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	check_if_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st))
		return (0);
	return (S_ISDIR(st.st_mode));
}

static char	**get_path_in_env(t_shell *shell)
{
	int		i;
	char	**path;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
		{
			path = ft_split(shell->env[i] + 5, ':');
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

static char	*build_full_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*ttmp;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	ttmp = ft_strjoin(tmp, cmd);
	free(tmp);
	return (ttmp);
}

char	*resolve_cmd_path(t_shell *shell, t_ast *ast)
{
	char	*tmp;
	char	**path;
	int		i;

	if (ft_strchr(ast->args_cmd[0], '/'))
	{
		if (access(ast->args_cmd[0], X_OK) != 0)
			return (NULL);
		return (ft_strdup(ast->args_cmd[0]));
	}
	path = get_path_in_env(shell);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = build_full_path(path[i], ast->args_cmd[0]);
		if (!tmp)
			return (ft_free_tab(path), NULL);
		if (access(tmp, X_OK) == 0 && !check_if_directory(tmp))
			return (ft_free_tab(path), tmp);
		free(tmp);
		i++;
	}
	return (ft_free_tab(path), NULL);
}
