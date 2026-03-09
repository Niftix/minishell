/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:19:52 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/10 00:11:42 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

void	print_token_type(t_token token)		//debug ft
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
		printf("token = \">\"\n");
	else if (token == TOKEN_LPAREN)
		printf("token = \"(\"\n");
	else if (token == TOKEN_RPAREN)
		printf("token = \")\"\n");
	else if (token == TOKEN_OUT)
		printf("token = \">\"\n");
	else if (token == TOKEN_EOF)
		printf("token = \"EOF\"\n");
	else if (token == TOKEN_WORD)
		printf("token = \"WORD\"\n");
}
