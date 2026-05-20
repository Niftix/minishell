#include "minishell.h"

int	pipe_no_cmd(t_ast *ast)
{
	if (ast->redirects && all_redirects(ast->redirects))
		return (1);
	return (0);
}

int	pipe_empty_cmd(t_shell *shell, t_ast *ast)
{
	if (ast->redirects && all_redirects(ast->redirects))
		return (1);
	ft_putstr_fd("minishell: : command not found\n", 2);
	return (127);
}
