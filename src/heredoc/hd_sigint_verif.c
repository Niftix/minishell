/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_sigint_verif.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:43:40 by mville            #+#    #+#             */
/*   Updated: 2026/05/18 23:58:29 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	hd_fail(t_redirect *redir, char *name)
{
	signal(SIGINT, sigint_handle);
	close(redir->fd);
	redir->fd = -1;
	unlink(name);
	free(name);
	return (1);
}

void	sigint_hd(int sig)
{
	(void)sig;
	g_status = 2;
	write(1, "\n", 1);
	rl_done = 1;
}
