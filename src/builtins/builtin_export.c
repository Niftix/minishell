/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:51:23 by mville            #+#    #+#             */
/*   Updated: 2026/04/10 13:41:36 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_var(t_shell *shell, char *arg)
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

static char	*make_join(char *old, char *arg)
{
	char	*tmp;
	char	*tmp2;
	char	*new;
	char	*name;

	name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg - 1);
	if (!name)
		return (NULL);
	tmp = ft_strjoin(name, "=");
	free(name);
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(old, ft_strchr(arg, '=') + 1);
	if (!tmp2)
		return (free(tmp), NULL);
	new = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (new);
}

static int	add_join(t_shell *shell, char *arg, int i)
{
	char	*tmp;

	if (i < 0)
	{
		tmp = make_join("", arg);
		if (!tmp)
			return (1);
		i = add_var(shell, tmp);
		return (free(tmp), i);
	}
	tmp = ft_strchr(shell->env[i], '=');
	if (!tmp)
		tmp = make_join("", arg);
	else
		tmp = make_join(tmp + 1, arg);
	if (!tmp)
		return (1);
	free(shell->env[i]);
	shell->env[i] = tmp;
	return (0);
}

static int	export_arg(t_shell *shell, char *arg, int *ret)
{
	int	j;

	if (exp_opt(arg))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(arg, 2);
		return (ft_putstr_fd(": invalid option\n", 2), 2);
	}
	if (!is_valid_id(arg))
		return (ft_putstr_fd("minishell: export: '", 2),
			ft_putstr_fd(arg, 2),
			ft_putstr_fd("': not a valid identifier\n", 2), *ret = 1, 0);
	if (!ft_strchr(arg, '='))
		return (j = find_var(shell, arg, 0), (j < 0) && add_var(shell, arg), 0);
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		return (add_join(shell, arg, find_var(shell, arg, 1)));
	j = find_var(shell, arg, 0);
	if (j < 0)
		return (add_var(shell, arg));
	free(shell->env[j]);
	shell->env[j] = ft_strdup(arg);
	return (0);
}

int	builtin_export(t_shell *shell, t_ast *ast)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!ast->args_cmd[1])
		return (print_export(shell), 0);
	while (ast->args_cmd[i])
	{
		if (export_arg(shell, ast->args_cmd[i], &ret) == 2)
			return (2);
		i++;
	}
	return (ret);
}
