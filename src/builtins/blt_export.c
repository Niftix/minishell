/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:51:23 by mville            #+#    #+#             */
/*   Updated: 2026/04/13 22:16:01 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_env_index(t_shell *shell, char *arg)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = 0;
	while (arg[name_len] && arg[name_len] != '=')
		name_len++;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], arg, name_len) == 0
			&& (shell->env[i][name_len] == '='
			|| shell->env[i][name_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static int	add_to_env(t_shell *shell, char *arg)
{
	int		i;
	char	**new_env;

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
	new_env[i] = ft_strdup(arg);
	if (!new_env[i])
		return (free(new_env), 1);
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

static int	setup_environment(t_shell *shell, char *arg)
{
	int		i;
	char	*new_value;

	i = find_env_index(shell, arg);
	if (i < 0)
		return (add_to_env(shell, arg));
	new_value = ft_strdup(arg);
	if (!new_value)
		return (1);
	free(shell->env[i]);
	shell->env[i] = new_value;
	return (0);
}

static int	export_with_arg(t_shell *shell, char *arg, int *status)
{
	if (!check_format_is_valid(arg))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*status = 1;
		return (0);
	}
	if (ft_strchr(arg, '='))
		return (setup_environment(shell, arg));
	if (find_env_index(shell, arg) >= 0)
		return (0);
	return (add_to_env(shell, arg));
}

int	blt_export(t_shell *shell, t_ast *ast)
{
	int	i;
	int	status;

	status = 0;
	if (!ast->args_cmd[1])
		return (no_arg_print_export(shell), 0);
	i = 1;
	while (ast->args_cmd[i])
	{
		if (export_with_arg(shell, ast->args_cmd[i], &status))
			return (1);
		i++;
	}
	return (status);
}
