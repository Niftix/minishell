/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:11:41 by mville            #+#    #+#             */
/*   Updated: 2026/05/19 12:01:30 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_env_index(t_shell *shell, char *name)
{
	int	name_len;
	int	i;

	name_len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, name_len) == 0
			&& (shell->env[i][name_len] == '='
			|| shell->env[i][name_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static int	add_new_value_to_env(t_shell *shell, char *new_value)
{
	char	**new_env;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = ft_strdup(new_value);
	if (!new_env[i])
		return (free(new_env), 1);
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

static int	set_env_value(t_shell *shell, char *name, char *value)
{
	char	*tmp;
	char	*arg;
	int		index;
	int		status;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (1);
	arg = ft_strjoin(tmp, value);
	free(tmp);
	if (!arg)
		return (1);
	index = find_env_index(shell, name);
	if (index >= 0)
	{
		free(shell->env[index]);
		shell->env[index] = arg;
		return (0);
	}
	status = add_new_value_to_env(shell, arg);
	free(arg);
	return (status);
}

static int	update_pwd_env(t_shell *shell, char *old_pwd)
{
	char	pwd_result[PATH_MAX];

	if (!getcwd(pwd_result, PATH_MAX))
		return (1);
	if (old_pwd && set_env_value(shell, "OLDPWD", old_pwd))
		return (1);
	return (set_env_value(shell, "PWD", pwd_result));
}

int	blt_cd(t_shell *shell, t_ast *ast)
{
	char	*path;
	char	*old_pwd;
	int		pwd_index;

	if (ast->args_cmd[1] && ast->args_cmd[2])
		return (ft_putstr_fd
			("minishell: cd: too many arguments\n", 2), 1);
	path = ast->args_cmd[1];
	if (!path)
		path = check_home(shell);
	if (!path)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(path) == -1)
	{
		cd_error(path);
		return (1);
	}
	old_pwd = NULL;
	pwd_index = find_env_index(shell, "PWD");
	if (pwd_index >= 0 && ft_strchr(shell->env[pwd_index], '='))
		old_pwd = ft_strchr(shell->env[pwd_index], '=') + 1;
	return (update_pwd_env(shell, old_pwd));
}
