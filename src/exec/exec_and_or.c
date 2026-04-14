/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:42:34 by mville            #+#    #+#             */
/*   Updated: 2026/04/14 17:25:20 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_and(t_shell *shell, t_ast *ast)
{
	int	status;

	status = ast_dispatch(shell, ast->left);
	if (status == 0)
		status = ast_dispatch(shell, ast->right);
	return (status);
}

int	exec_or(t_shell *shell, t_ast *ast)
{
	int	status;

	status = ast_dispatch(shell, ast->left);
	if (status != 0)
		status = ast_dispatch(shell, ast->right);
	return (status);
}
