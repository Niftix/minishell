/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:23:26 by mville            #+#    #+#             */
/*   Updated: 2026/05/20 17:58:38 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;

void	sigint_handle(int sigint)
{
	(void)sigint;
	g_status = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_interactive(void)
{
	signal(SIGINT, sigint_handle);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_init(void)
{
	g_status = 0;
	signal_interactive();
}
