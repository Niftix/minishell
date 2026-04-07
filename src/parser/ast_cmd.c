/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:58:24 by mville            #+#    #+#             */
/*   Updated: 2026/04/07 12:58:25 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_words(t_lexer *tok)
{
	int	n;

	n = 0;
	while (tok && cmd_token_checker(tok->type))
	{
		if (tok->type == TOKEN_WORD)
			n++;
		else if (tok->next)
			tok = tok->next;
		tok = tok->next;
	}
	return (n);
}

static t_ast	*fill_simple_cmd(t_ast *node, t_lexer **cur)
{
	int	i;

	i = 0;
	while (*cur && cmd_token_checker((*cur)->type))
	{
		if ((*cur)->type == TOKEN_WORD)
		{
			node->args_cmd[i++] = ft_strdup((*cur)->value);
			*cur = (*cur)->next;
		}
		else if (parse_one_redirect(cur, &node->redirects))
			return (ast_free(node), NULL);
	}
	node->args_cmd[i] = NULL;
	return (node);
}

t_ast	*ast_simple_cmd(t_lexer **cur)
{
	t_ast	*node;
	int		n;

	if (!*cur || !cmd_token_checker((*cur)->type))
		return (NULL);
	n = count_words(*cur);
	node = create_ast_node(AST_CMD);
	if (!node)
		return (NULL);
	node->args_cmd = malloc(sizeof(char *) * (n + 1));
	if (!node->args_cmd)
		return (free(node), NULL);
	return (fill_simple_cmd(node, cur));
}

t_ast	*ast_cmd(t_lexer **cur)
{
	t_ast	*node;

	if (!*cur)
		return (NULL);
	if ((*cur)->type != TOKEN_LPAREN)
		return (parse_simple_cmd(cur));
	*cur = (*cur)->next;
	node = create_ast_node(AST_SUBSHELL);
	if (!node)
		return (NULL);
	node->left = parse_and_or(cur);
	if (!node->left || !*cur || (*cur)->type != TOKEN_RPAREN)
		return (ast_free(node), NULL);
	*cur = (*cur)->next;
	while (*cur && redirect_checker((*cur)->type))
		if (parse_one_redirect(cur, &node->redirects))
			return (ast_free(node), NULL);
	return (node);
}
