/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 18:15:01 by mville            #+#    #+#             */
/*   Updated: 2026/03/10 21:44:01 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_ast *ast)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (ast->args_cmd[1] && ft_strcmp(ast->args_cmd[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (ast->args_cmd[i])
	{
		ft_putstr_fd(ast->args_cmd[i], 1);
		if (ast->args_cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	builtin_pwd(void)
{
	char	result[PATH_MAX];

	if (!getcwd(result, PATH_MAX))
		return (1);
	ft_putstr_fd(result, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

int	builtin_cd(t_shell *shell, t_ast *ast)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*dir;

	if (ast->args_cmd[1] && ast->args_cmd[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	dir = ast->args_cmd[1];
	if (!dir)
		dir = find_home(shell);
	if (!dir)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (!getcwd(old_pwd, PATH_MAX))
		return (1);
	if (cd_chdir(dir))
		return (1);
	if (!getcwd(new_pwd, PATH_MAX))
		return (1);
	return (update_env(shell, old_pwd, new_pwd));
}

int	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd(shell->env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}

int	builtin_exit(t_shell *shell, t_ast *ast)
{
	ft_putstr_fd("exit\n", 1);
	if (!ast->args_cmd[1])
		return (shell->run = 0, shell->status_exit);
	if (ast->args_cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (!exit_is_num(ast->args_cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(ast->args_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (shell->run = 0, 2);
	}
	shell->run = 0;
	return (ft_atoi(ast->args_cmd[1]) & 0xFF);
}
