/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:19:52 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/10 14:36:29 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*creat_new_node(char *input, size_t idx, int status)
{
	t_lexer	*new_lex;

	new_lex = malloc(sizeof(t_lexer));
	if (!new_lex)
		return (NULL);
	new_lex->next = NULL;
	if (status == 1)
		new_lex->type = tokeniser(input, &idx);
	else
		new_lex->type = EOF;
	new_lex->value = NULL;
	if (new_lex->type == TOKEN_WORD)
		new_lex->value = set_value(input, idx);
	return (new_lex);
}

int	ft_lexadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*temp;

	if (!new || !lst)
		return (1);
	if (!*lst)
	{
		*lst = new;
		return (0);
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return (0);
}

void	ft_lexclear(t_lexer **lst, void (*del)(void *))
{
	t_lexer	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->value);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

//debug ft

void	print_token_type(t_token token)
{
	if (token == TOKEN_AND)
		printf("token = \"&&\"\n");
	else if (token == TOKEN_OR)
		printf("token = \"||\"\n");
	else if (token == TOKEN_PIPE)
		printf("token = \"|\"\n");
	else if (token == TOKEN_APPEND_OUT)
		printf("token = \">>\"\n");
	else if (token == TOKEN_HERE_DOC)
		printf("token = \"<<\"\n");
	else if (token == TOKEN_IN)
		printf("token = \"<\"\n");
	else if (token == TOKEN_LPAREN)
		printf("token = \"(\"\n");
	else if (token == TOKEN_RPAREN)
		printf("token = \")\"\n");
	else if (token == TOKEN_OUT)
		printf("token = \">\"\n");
	else if (token == EOF)
		printf("token = \"EOF\"\n");
	else if (token == TOKEN_WORD)
		printf("token = \"WORD\"\n");
}
