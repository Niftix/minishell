/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:35:00 by mville            #+#    #+#             */
/*   Updated: 2026/03/24 11:31:33 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_lexer	*lexer;
	char	*input;

	(void)ac;
	(void)av;
	signal_init();
	if (shell_init(&shell, envp) == 1)
		return (1);
	while (shell.run)
	{
		input = get_input(&shell);
		if (input)
		{
			lexer = lexer_creat(input, av[0]);
			if (!lexer)
				return (free(input), 1); //malloc faile
			/* PARSER*/
		lex_lexclear(&lexer, free);
			/* EXEC */
		}
		free(input);
	}
	free_and_clean_history(&shell);
	return (shell.status_exit);
}
