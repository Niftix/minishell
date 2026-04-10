/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:02:50 by mville            #+#    #+#             */
/*   Updated: 2026/04/10 23:31:06 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_new(t_shell *shell, char *arg)
{
	char	*av[3];
	t_ast	tmp;

	av[0] = "export";
	av[1] = arg;
	av[2] = NULL;
	tmp.args_cmd = av;
	builtin_export(shell, &tmp);
}

static void	assign_one(t_shell *shell, char *arg)
{
	int	j;

	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		return ((void)assign_new(shell, arg));
	j = find_var(shell, arg, 0);
	if (j < 0)
		return ((void)assign_new(shell, arg));
	free(shell->env[j]);
	shell->env[j] = ft_strdup(arg);
}

int	builtin_assign(t_shell *shell, t_ast *ast)
{
	int	i;

	i = 0;
	while (ast->args_cmd[i])
		if (!ft_strchr(ast->args_cmd[i++], '='))
			return (-1);
	i = 0;
	while (ast->args_cmd[i])
		assign_one(shell, ast->args_cmd[i++]);
	return (0);
}
