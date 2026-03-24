#include "parser.h"

static t_ast	*ast_parse_pipeline(t_lexer **cur)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_cmd(cur);
	if (!left)
		return (NULL);
	while (*cur && (*cur)->type == TOKEN_PIPE)
	{
		*cur = (*cur)->next;
		node = create_ast_node(AST_PIPE);
		if (!node)
			return (ast_free(left), NULL);
		node->left = left;
		node->right = parse_cmd(cur);
		if (!node->right)
			return (ast_free(node), NULL);
		left = node;
	}
	return (left);
}

t_ast	*ast_and_or(t_lexer **cur)
{
	t_ast		*left;
	t_ast		*node;
	t_ast_type	type;

	left = parse_pipeline(cur);
	if (!left)
		return (NULL);
	while (*cur && ((*cur)->type == TOKEN_AND || (*cur)->type == TOKEN_OR))
	{
		type = AST_OR;
		if ((*cur)->type == TOKEN_AND)
			type = AST_AND;
		*cur = (*cur)->next;
		node = create_ast_node(type);
		if (!node)
			return (ast_free(left), NULL);
		node->left = left;
		node->right = parse_pipeline(cur);
		if (!node->right)
			return (ast_free(node), NULL);
		left = node;
	}
	return (left);
}

t_ast	*ast_parse(t_lexer *lex)
{
	if (!lex || lex->type == TOKEN_ERROR || lex->type == TOKEN_EOF)
		return (NULL);
	return (parse_and_or(&lex));
}
