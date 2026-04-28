/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:31:35 by mville            #+#    #+#             */
/*   Updated: 2026/04/28 16:45:35 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast	*build_ast_node(t_ast_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = create_ast_node(type);
	if (!node)
		return (ast_free(left), ast_free(right), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

static t_ast	*parse_pipeline(t_lexer **current, t_shell *shell)
{
	t_ast	*node;

	node = parse_cmd(current, shell);
	while (node && *current && (*current)->type == TOKEN_PIPE)
	{
		*current = (*current)->next;
		node = build_ast_node(AST_PIPE, node, parse_cmd(current, shell));
	}
	return (node);
}

t_ast	*parse_and_or(t_lexer **current, t_shell *shell)
{
	t_ast		*node;
	t_ast_type	type;

	node = parse_pipeline(current, shell);
	while (node && *current && ((*current)->type == TOKEN_AND
			|| (*current)->type == TOKEN_OR))
	{
		type = AST_OR;
		if ((*current)->type == TOKEN_AND)
			type = AST_AND;
		*current = (*current)->next;
		node = build_ast_node(type, node, parse_pipeline(current, shell));
	}
	return (node);
}

static void	token_error_check_hd(t_lexer *lex, t_shell *shell)
{
	if (resolve_token_error_with_hd(lex, shell))
		shell->status_exit = 1;
	else
	{
		if (lex->value)
			parser_put_error(NULL);
		shell->status_exit = 2;
	}
}

t_ast	*check_parse(t_lexer *lex, t_shell *shell)
{
	t_ast	*ast;

	if (!lex || lex->type == TOKEN_EOF)
		return (NULL);
	if (lex->type == TOKEN_ERROR)
	{
		token_error_check_hd(lex, shell);
		return (NULL);
	}
	ast = parse_and_or(&lex, shell);
	if (!ast && shell->status_exit == 1)
		return (NULL);
	if (!ast || (lex && lex->type != TOKEN_EOF))
	{
		parser_put_error(lex);
		shell->status_exit = 2;
		return (ast_free(ast), NULL);
	}
	return (ast);
}
