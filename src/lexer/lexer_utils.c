/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:19:52 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/24 15:41:04 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*lex_creat_new_node(char *input, size_t idx, int status)
{
	t_lexer	*new_lex;

	new_lex = malloc(sizeof(t_lexer));
	if (!new_lex)
		return (NULL);
	new_lex->next = NULL;
	if (status == 1)
		new_lex->type = lex_tokeniser(input, &idx);
	else
		new_lex->type = EOF;
	new_lex->value = NULL;
	if (new_lex->type == TOKEN_WORD)
	{
		new_lex->value = lex_set_value(input, idx);
		if (!new_lex->value)
			return (free(new_lex), NULL);
	}
	return (new_lex);
}

t_lexer	*lex_cpy_node(t_lexer *old)
{
	t_lexer	*new_lex;

	new_lex = malloc(sizeof(t_lexer));
	if (!new_lex)
		return (NULL);
	new_lex->next = NULL;
	new_lex->value = NULL;
	new_lex->type = old->type;
	if (old->value)
	{
		new_lex->value = ft_strdup(old->value);
		if (!new_lex->value)
			return (free(new_lex), NULL);
	}
	return (new_lex);
}

int	lex_lexadd_back(t_lexer **lst, t_lexer *new)
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

void	lex_lexclear(t_lexer **lst, void (*del)(void *))
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
