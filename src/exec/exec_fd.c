/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 23:18:47 by mville            #+#    #+#             */
/*   Updated: 2026/05/18 23:19:33 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_save(t_shell *shell)
{
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	if (shell->stdin_backup == -1 || shell->stdout_backup == -1)
		return (1);
	return (0);
}

void	fd_recovery(t_shell *shell)
{
	dup2(shell->stdin_backup, STDIN_FILENO);
	dup2(shell->stdout_backup, STDOUT_FILENO);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	shell->stdin_backup = -1;
	shell->stdout_backup = -1;
}
