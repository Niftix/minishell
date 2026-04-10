/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:31:28 by mville            #+#    #+#             */
/*   Updated: 2026/04/07 14:02:41 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	add_token(t_ast *node, t_lexer **cur, t_shell *shell, int *count)
{
	t_lexer	*tmp;

	if (is_io_nb(*cur))
	{
		tmp = (*cur)->next;
		if (parse_one_redirect(&tmp, &node->redirects, ft_atoi((*cur)->value)))
			return (1);
		*cur = tmp;
		return (0);
	}
	if ((*cur)->type != TOKEN_WORD)
		return (parse_one_redirect(cur, &node->redirects, -1));
	if (add_arg_cmd(node, *cur, shell, count))
		return (1);
	*cur = (*cur)->next;
	return (0);
}

static t_ast	*fill_simple_cmd(t_ast *node, t_lexer **cur, t_shell *shell)
{
	int	count;

	count = 0;
	node->args_cmd = malloc(sizeof(char *));
	if (!node->args_cmd)
		return (ast_free(node), NULL);
	node->args_cmd[0] = NULL;
	while (*cur && cmd_token_checker((*cur)->type))
		if (add_token(node, cur, shell, &count))
			return (ast_free(node), NULL);
	return (node);
}

t_ast	*parse_simple_cmd(t_lexer **cur, t_shell *shell)
{
	t_ast	*node;

	if (!*cur || !cmd_token_checker((*cur)->type))
		return (NULL);
	node = create_ast_node(AST_CMD);
	if (!node)
		return (NULL);
	return (fill_simple_cmd(node, cur, shell));
}

t_ast	*parse_cmd(t_lexer **cur, t_shell *shell)
{
	t_ast	*node;

	if (!*cur)
		return (NULL);
	if ((*cur)->type != TOKEN_LPAREN)
		return (NULL);
	*cur = (*cur)->next;
	node = create_ast_node(AST_GROUP);
	if (!node)
		return (NULL);
	node->left = parse_and_or(cur, shell);
	if (!node->left || !*cur || (*cur)->type != TOKEN_RPAREN)
		return (ast_free(node), NULL);
	*cur = (*cur)->next;
	return (node);
}
