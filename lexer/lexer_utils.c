/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:19:52 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/05 17:15:49 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	set_token_type(char *value, t_token_type *type)
{
	ft_bzero(type, sizeof(t_token_type));
	if (ft_strlen(value) == 1 && value[0] == '|')
		type->pipe = 1;
	else if (ft_strlen(value) == 1 && value[0] == '<')
		type->in = 1;
	else if (ft_strlen(value) == 1 && value[0] == '>')
		type->out = 1;
	else if (ft_strlen(value) == 2 && value[0] == '<' && value[1] == '<')
		type->here_doc = 1;
	else if (ft_strlen(value) == 2 && value[0] == '>' && value[1] == '>')
		type->append_out = 1;
	else if (ft_strlen(value) == 2 && value[0] == '|' && value[1] == '|')
		type->append_out = 1;
	else if (ft_strlen(value) == 2 && value[0] == '&' && value[1] == '&')
		type->append_out = 1;
	else
		type->word = 1;
}

static char *set_lex_value(char *value, t_token_type type)
{
	char *res;
	ssize_t len;

	if (type.in)
		res = ft_strdup("[Redirect:IN]");
	else if (type.out)
		res = ft_strdup("[Redirect:OUT]");
	else if (type.here_doc)
		res = ft_strdup("[HERE_DOC]");
	else if (type.append_out)
		res = ft_strdup("[APPEND:OUT]");
	else if (type.pipe)
		res = ft_strdup("[PIPE]");
	else if (type.is_and)
		res = ft_strdup("[AND]");
	else if (type.is_or)
		res = ft_strdup("[OR]");
	else if (type.word)
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

