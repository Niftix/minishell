/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 18:15:01 by mville            #+#    #+#             */
/*   Updated: 2026/04/10 13:41:43 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	builtin_env(t_shell *shell, t_ast *ast)
{
	int	i;

	if (ast->args_cmd[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(ast->args_cmd[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		return (127);
	}
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
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 1);
	if (!ast->args_cmd[1])
		return (shell->run = 0, shell->status_exit);
	if (!ast->args_cmd[1][0] || !exit_is_num(ast->args_cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(ast->args_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (shell->run = 0, 2);
	}
	if (ast->args_cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	shell->run = 0;
	return ((unsigned char)ft_atol(ast->args_cmd[1]));
}
