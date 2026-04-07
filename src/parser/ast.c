/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:58:32 by mville            #+#    #+#             */
/*   Updated: 2026/04/07 12:58:32 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*create_ast_node(t_ast_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args_cmd = NULL;
	node->redirects = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_redirect	*redirect_new(t_redirect_type type, char *target)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->fd = -1;
	redir->target = ft_strdup(target);
	if (!redir->target)
		return (free(redir), NULL);
	redir->next = NULL;
	return (redir);
}

void	redirect_add_end(t_redirect **lst, t_redirect *new)
{
	t_redirect	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ast_free(t_ast *ast)
{
	t_redirect	*redir;
	t_redirect	*tmp;

	if (!ast)
		return ;
	ast_free(ast->left);
	ast_free(ast->right);
	ft_free_tab(ast->args_cmd);
	redir = ast->redirects;
	while (redir)
	{
		tmp = redir->next;
		free(redir->target);
		free(redir);
		redir = tmp;
	}
	free(ast);
}
