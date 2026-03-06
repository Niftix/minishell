/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:31:33 by mville            #+#    #+#             */
/*   Updated: 2026/03/06 14:30:35 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ast_dispatch(t_shell *shell, t_ast *ast)
{
 if (!ast)
  return (0);
 if (ast->type == AST_CMD)
  //exec node
 else if (ast->type == AST_PIPE)
  // exec pipe
 else if (ast->type == AST_AND)
  // exec and
 else if (ast->type == AST_OR)
  // exec or
 return (1);
}

