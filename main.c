/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:35:00 by mville            #+#    #+#             */
/*   Updated: 2026/03/05 16:42:52 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handle(int sigint)
{
	(void)sigint;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*input;

	signal(SIGINT, sigint_handle);
	signal(SIGQUIT, SIG_IGN);
	if (shell_init(&shell, envp) == 1)
		return (1);
	while (shell.run)
	{
		input = readline("minishell > ");
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			shell.run = 0;
		}
		else
		{
			if (input[0] != '\0')
				add_history(input);
		}
    //PARSE + EXEC
		free(input);
	}
	rl_clear_history();
	return (0);
}
