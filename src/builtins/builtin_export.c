/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:51:23 by mville            #+#    #+#             */
/*   Updated: 2026/03/10 19:32:22 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_one(char *entry)
{
	char	*equal;
	int		name_len;
	int		j;

	equal = ft_strchr(entry, '=');
	ft_putstr_fd("declare -x ", 1);
	if (!equal)
	{
		ft_putstr_fd(entry, 1);
		ft_putstr_fd("\n", 1);
		return ;
	}
	name_len = equal - entry + 1;
	j = 0;
	while (j < name_len)
	{
		write(1, &entry[j], 1);
		j++;
	}
	ft_putstr_fd("\"", 1);
	ft_putstr_fd(equal + 1, 1);
	ft_putstr_fd("\"\n", 1);
}

static void	print_all(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		print_one(shell->env[i]);
		i++;
	}
}

static int	env_update(t_shell *shell, char *arg)
{
	int		i;
	int		name_len;
	char	*equal;

	i = 0;
	equal = ft_strchr(arg, '=');
	if (!equal || equal == arg)
		return (0);
	name_len = equal - arg + 1;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], arg, name_len) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(arg);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	env_add(t_shell *shell, char *arg)
{
	char	**new;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (1);
	i = 0;
	while (shell->env[i])
	{
		new[i] = shell->env[i];
		i++;
	}
	new[i] = ft_strdup(arg);
	if (!new[i])
	{
		free(new);
		return (1);
	}
	new[i + 1] = NULL;
	free(shell->env);
	shell->env = new;
	return (0);
}

int	builtin_export(t_shell *shell, t_ast *ast)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!ast->args_cmd[1])
		return (print_all(shell), 0);
	while (ast->args_cmd[i])
	{
		if (!is_valid_id(ast->args_cmd[i]))
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(ast->args_cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret = 1;
		}
		else if (env_update(shell, ast->args_cmd[i]) == 1)
			env_add(shell, ast->args_cmd[i]);
		i++;
	}
	return (ret);
}
