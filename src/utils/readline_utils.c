/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:15:14 by mville            #+#    #+#             */
/*   Updated: 2026/04/10 13:10:13 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"

static char	*input_gnl(void)
{
	char	*line;
	char	*input;

	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	input = ft_strtrim(line, "\n");
	free(line);
	return (input);
}

char	*get_input(t_shell *shell)
{
	char	*input;

	if (isatty(STDIN_FILENO))
		input = readline("minishell > ");
	else
		input = input_gnl();
	if (input == NULL)
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 5);
		shell->run = 0;
		return (NULL);
	}
	if (isatty(STDIN_FILENO) && input[0] != '\0')
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
	get_next_line(-1);
	rl_clear_history();
	if (shell->env)
	{
		ft_free_tab(shell->env);
		shell->env = NULL;
	}
}

void	child_exit(t_shell *shell, int status)
{
	free_shell(shell);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(status);
}
