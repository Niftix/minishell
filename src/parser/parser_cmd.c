/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:31:28 by mville            #+#    #+#             */
/*   Updated: 2026/04/07 13:01:22 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**add_expanded_args(char **args, char **words, int *count)
{
	char	**new;
	int		i;

	i = 0;
	while (words[i])
		i++;
	new = ft_realloc(args, sizeof(char *) * (*count + 1),
			sizeof(char *) * (*count + i + 1));
	if (!new)
		return (ft_free_tab(words), NULL);
	i = 0;
	while (words[i])
	{
		new[*count] = remove_quote(words[i]);
		free(words[i]);
		(*count)++;
		i++;
	}
	new[*count] = NULL;
	free(words);
	return (new);
}

static t_ast	*fill_simple_cmd(t_ast *node, t_lexer **cur, t_shell *shell)
{
	char	**words;
	int		count;
	count = 0;
	node->args_cmd = malloc(sizeof(char *));
	if (!node->args_cmd)
		return (ast_free(node), NULL);
	node->args_cmd[0] = NULL;
	while (*cur && cmd_token_checker((*cur)->type))
	{
		if ((*cur)->type == TOKEN_WORD)
		{
			words = expand(ft_strdup((*cur)->value), shell->env, shell->status_exit);
			if (!words)
				return (ast_free(node), NULL);
			node->args_cmd = add_expanded_args(node->args_cmd, words, &count);
			if (!node->args_cmd)
				return (ast_free(node), NULL);
			*cur = (*cur)->next;
		}
		else if (parse_one_redirect(cur, &node->redirects))
			return (ast_free(node), NULL);
	}
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
		return (parse_simple_cmd(cur, shell));
	*cur = (*cur)->next;
	node = create_ast_node(AST_SUBSHELL);
	if (!node)
		return (NULL);
	node->left = parse_and_or(cur, shell);
	if (!node->left || !*cur || (*cur)->type != TOKEN_RPAREN)
		return (ast_free(node), NULL);
	*cur = (*cur)->next;
	while (*cur && redirect_checker((*cur)->type))
		if (parse_one_redirect(cur, &node->redirects))
			return (ast_free(node), NULL);
	return (node);
}
