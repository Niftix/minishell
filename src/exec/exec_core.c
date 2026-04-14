/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:31:33 by mville            #+#    #+#             */
/*   Updated: 2026/04/14 17:25:24 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ast_dispatch(t_shell *shell, t_ast *ast)
{
	if (!ast)
		return (0);
	if (ast->type == AST_CMD)
		return (exec_cmd(shell, ast));
	else if (ast->type == AST_PIPE)
		return (exec_pipe(shell, ast));
	else if (ast->type == AST_AND)
		return (exec_and(shell, ast));
	else if (ast->type == AST_OR)
		return (exec_or(shell, ast));
	else if (ast->type == AST_GROUP)
		return (exec_group(shell, ast));
	return (1);
}
