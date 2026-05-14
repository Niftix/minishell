
#include "parser.h"

int	hd_fail(t_redirect *redir, char *name)
{
	signal(SIGINT, sigint_handle);
	close(redir->fd);
	redir->fd = -1;
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
