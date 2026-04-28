/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:15:14 by mville            #+#    #+#             */
/*   Updated: 2026/04/28 12:39:04 by mville           ###   ########.fr       */
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
