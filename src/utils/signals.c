/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:23:26 by mville            #+#    #+#             */
/*   Updated: 2026/04/14 14:30:26 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;

static void	sigint_handle(int sigint)
{
	(void)sigint;
	g_status = 2;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_init(void)
{
	g_status = 0;
	signal(SIGINT, sigint_handle);
	signal(SIGQUIT, SIG_IGN);
}
