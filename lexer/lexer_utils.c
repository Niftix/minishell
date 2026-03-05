/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:19:52 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/05 18:04:25 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	set_token_type(char *value, t_token *type)
{
	if (ft_strlen(value) == 1 && value[0] == '|')
		*type = TOKEN_PIPE;
	else if (ft_strlen(value) == 1 && value[0] == '<')
		*type = TOKEN_IN;
	else if (ft_strlen(value) == 1 && value[0] == '>')
		*type = TOKEN_OUT;
	else if (ft_strlen(value) == 2 && value[0] == '<' && value[1] == '<')
		*type = TOKEN_HERE_DOC;
	else if (ft_strlen(value) == 2 && value[0] == '>' && value[1] == '>')
		*type = TOKEN_APPEND_OUT;
	else if (ft_strlen(value) == 2 && value[0] == '|' && value[1] == '|')
		*type = TOKEN_OR;
	else if (ft_strlen(value) == 2 && value[0] == '&' && value[1] == '&')
		*type = TOKEN_AND;
	else
		*type = TOKEN_WORD;
}

static char *set_lex_value(char *value, t_token type)
{
	char *res;
	ssize_t len;

	res = NULL;
	if (type == TOKEN_IN)
		res = ft_strdup("[Redirect:IN]");
	else if (type == TOKEN_OUT)
		res = ft_strdup("[Redirect:OUT]");
	else if (type == TOKEN_HERE_DOC)
		res = ft_strdup("[HERE_DOC]");
	else if (type == TOKEN_APPEND_OUT)
		res = ft_strdup("[APPEND:OUT]");
	else if (type == TOKEN_PIPE)
		res = ft_strdup("[PIPE]");
	else if (type == TOKEN_AND)
		res = ft_strdup("[AND]");
	else if (type == TOKEN_OR)
		res = ft_strdup("[OR]");
	else if (type == TOKEN_WORD)
	{
		res = ft_strdup("[WORD:");
		len = 7;
		ft_strdupcat(res, value, &len, ft_strlen(value));
	}
	return (res);
}

t_lexer	*ft_lexnew(char *value)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	set_token_type(value, &new->type);
	new->value = set_lex_value(value, new->type);
	if (!new->value);
		return (NULL);			// need to handle malloc error
	new->next = NULL;
	return (new);
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

