/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:35:00 by mville            #+#    #+#             */
/*   Updated: 2026/04/07 13:56:32 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"

static int	process_input(t_shell *shell, char *input, char **av)
{
	t_lexer	*lexer;
	t_ast	*ast;

	lexer = lexer_creat(input, av[0], &shell->status_exit);
	if (!lexer)
		return (1);
	ast = check_parse(lexer, shell);
	if (ast)
	{
		hd_resolve(ast, shell);
		shell->status_exit = ast_dispatch(shell, ast);
		ast_free(ast);
	}
	lex_lexclear(&lexer, free);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)ac;
	signal_init();
	if (shell_init(&shell, envp) == 1)
		return (1);
	while (shell.run)
	{
		input = get_input(&shell);
		if (input && process_input(&shell, input, av))
			return (free(input), 1);
		free(input);
	}
	free_and_clean_history(&shell);
	return (shell.status_exit);
}
