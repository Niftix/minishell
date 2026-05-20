/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_sigint_verif.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:43:40 by mville            #+#    #+#             */
/*   Updated: 2026/05/20 17:19:45 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	hd_fail(t_redirect *redir, char *name)
{
	signal_interactive();
	close(redir->fd);
	redir->fd = -1;
	unlink(name);
	free(name);
	return (1);
}

void	sigint_hd(int sig)
{
	(void)sig;
	g_status = SIGINT;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	rl_done = 1;
}
