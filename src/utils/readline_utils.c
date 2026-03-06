/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:15:14 by mville            #+#    #+#             */
/*   Updated: 2026/03/06 14:12:06 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_and_clean_history(t_shell *shell)
{
	rl_clear_history();
	ft_free_tab(shell->env);
}
