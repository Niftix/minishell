/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:15:14 by mville            #+#    #+#             */
/*   Updated: 2026/04/25 18:40:30 by vcucuiet         ###   ########.fr       */
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

static char	*read_input(t_shell *shell)
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
	}
	return (input);
}

char	*get_input(t_shell *shell)
{
	char	*input;

	input = get_stash_line(&shell->input_stash);
	if (input)
	{
		if (isatty(STDIN_FILENO) && input[0] != '\0')
			add_history(input);
		return (input);
	}
	input = read_input(shell);
	if (!input)
		return (NULL);
	if (isatty(STDIN_FILENO))
		input = check_multi_line(&shell->input_stash, input);
	if (!input)
		return (shell->run = 0, NULL);
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
	clean_static_var();
}

void	free_shell(t_shell *shell)
{
	clean_loop(shell);
	clean_stash(&shell->input_stash);
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
