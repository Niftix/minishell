/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:31:33 by mville            #+#    #+#             */
/*   Updated: 2026/03/09 10:58:06 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_cmd(t_shell *shell, t_ast *ast)
{
 int status;
 char *path;
 pid_t pid;

 if (check_builtins(ast))
  //sur fonction exec builtins
 pid = fork();
 if (pid == -1)
 return(1);
 if (pid == 0)
 {
  path = find_path(shell, ast);
  if (!path)
   exit(127);
  execve(path, ast->args_cmd, shell->env);
  exit(126);
 }
 waitpid(pid, &status, 0);
 return (WEXITSTATUS(status));
}
int exec_pipe(t_shell *shell, t_ast *ast)
{

}

int exec_and(t_shell *shell, t_ast *ast)
{

}

int exec_or(t_shell *shell, t_ast *ast)
{

}
int ast_dispatch(t_shell *shell, t_ast *ast)
{
 if (!ast)
  return (0);
 if (ast->type == AST_CMD)
  return(exec_cmd(shell, ast));
 else if (ast->type == AST_PIPE)
  // exec pipe
 else if (ast->type == AST_AND)
  // exec and
 else if (ast->type == AST_OR)
  // exec or
 return (1);
}

