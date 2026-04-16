/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:15:14 by mville            #+#    #+#             */
/*   Updated: 2026/04/14 15:02:16 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"

char	*get_input(t_shell *shell)
{
	char	*input;

	input = readline("minishell > ");
	if (input == NULL)
	{
		write(1, "exit\n", 5);
		shell->run = 0;
		return (NULL);
	}
	if (input[0] != '\0')
		add_history(input);
	return (input);
}

void	clean_loop(t_shell *shell)
{
	if (shell->t_current_ast)
	{
		ast_free(shell->t_current_ast);
		shell->t_current_ast = NULL;
	}
	if (shell->t_current_lexer)
		lex_lexclear(&shell->t_current_lexer, free);
	if (shell->current_input)
	{
		free(shell->current_input);
		shell->current_input = NULL;
	}
}

void	free_shell(t_shell *shell)
{
	clean_loop(shell);
	rl_clear_history();
	if (shell->env)
	{
		ft_free_tab(shell->env);
		shell->env = NULL;
	}
}

void	child_exit(t_shell *shell, int status)
{
	clean_loop(shell);
	exit(status);
}
