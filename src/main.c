/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:35:00 by mville            #+#    #+#             */
/*   Updated: 2026/04/16 16:47:28 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"

static int	process_input(t_shell *shell, char *input)
{
	shell->current_input = input;
	shell->t_current_lexer = lexer_creat(input, &shell->status_exit);
	if (!shell->t_current_lexer)
		return (1);
	if (shell->t_current_lexer->type == TOKEN_ERROR && !isatty(STDIN_FILENO))
		shell->run = 0;
	shell->t_current_ast = check_parse(shell->t_current_lexer, shell);
	if (shell->t_current_ast)
	{
		hd_resolve(shell->t_current_ast, shell);
		shell->status_exit = ast_dispatch(shell, shell->t_current_ast);
	}
	clean_loop(shell);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)ac;
	(void)av;
	signal_init();
	if (shell_init(&shell, envp) == 1)
		return (1);
	while (shell.run)
	{
		input = get_input(&shell);
		if (g_status != 0)
		{
			shell.status_exit = 128 + g_status;
			g_status = 0;
		}
		if (input && process_input(&shell, input))
		{
			free_shell(&shell);
			return (1);
		}
	}
	free_shell(&shell);
	return (shell.status_exit);
}
