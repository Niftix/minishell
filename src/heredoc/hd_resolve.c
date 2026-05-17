/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_resolve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:31:23 by mville            #+#    #+#             */
/*   Updated: 2026/05/14 22:48:02 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	hd_resolve(t_ast *ast, t_shell *shell)
{
	t_redirect	*tmp;

	if (!ast)
		return (0);
	tmp = ast->redirects;
	if (hd_resolve(ast->left, shell))
		return (1);
	if (hd_resolve(ast->right, shell))
		return (1);
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC)
			if (read_hd(tmp, shell))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}
