#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_ast	node;
	t_ast	left;
	t_ast	right;
	t_ast	pipe_node;
	char	*args1[] = {"echo", "hello", "world", NULL}; 	/* test1 */
	char	*args2[] = {"pwd", NULL}; 	/* test 2 */
	char	*largs[] = {"echo", "hello", NULL}; 	/* test 3 */
	char	*rargs[] = {"cat", NULL};  	/* test 3 */

	(void)ac;
	(void)av;
	shell.env = envp;
	shell.status_exit = 0;
	shell.run = 1;
	shell.stdin_backup = -1;
	shell.stdout_backup = -1;

	/* test1 */
	node.type = AST_CMD;
	node.args_cmd = args1;
	node.redirects = NULL;
	node.left = NULL;
	node.right = NULL;
	ast_dispatch(&shell, &node);

	/* test 2 */
	node.args_cmd = args2;
	ast_dispatch(&shell, &node);

	/* test 3 */
	left.type = AST_CMD;
	left.args_cmd = largs;
	left.redirects = NULL;
	left.left = NULL;
	left.right = NULL;
	right.type = AST_CMD;
	right.args_cmd = rargs;
	right.redirects = NULL;
	right.left = NULL;
	right.right = NULL;
	pipe_node.type = AST_PIPE;
	pipe_node.args_cmd = NULL;
	pipe_node.redirects = NULL;
	pipe_node.left = &left;
	pipe_node.right = &right;
	ast_dispatch(&shell, &pipe_node);

	return (0);
}
