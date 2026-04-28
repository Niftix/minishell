/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:36:29 by mville            #+#    #+#             */
/*   Updated: 2026/04/26 20:54:19 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **res)
{
	int	i;

	if (!res)
		return ;
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
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

void	clean_stash(t_input_stash *input_stash)
{
	free(input_stash->stash);
	input_stash->stash = NULL;
	input_stash->idx = 0;
}
