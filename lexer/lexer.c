/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:50:00 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/10 11:30:49 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

size_t	skip_tab_space_nl(char *input, size_t start)
{
	size_t	idx;

	idx = start;
	while (input[idx] && (input[idx] == '\t'
			|| input[idx] == ' ' || input[idx] == '\n'))
		idx++;
	return (idx);
}

size_t	token_len(t_token token)
{
	if (token == TOKEN_AND || token == TOKEN_APPEND_OUT
		|| token == TOKEN_HERE_DOC || token == TOKEN_OR)
		return (2);
	return (1);
}

t_lexer	*lexer(char *input)
{
	t_lexer	*lex;
	t_lexer	*tmp;
	size_t	i;
	size_t	input_len;

	i = 0;
	lex = NULL;
	input_len = ft_strlen(input);
	while (i < input_len)
	{
		i = skip_tab_space_nl(input, i);
		tmp = creat_new_node(input, i, 1);
		if (!tmp)
			return (ft_lexclear(&lex, free), NULL); //need malloc failed error
		if (tmp->type != TOKEN_WORD)
			i += token_len(tmp->type);
		else
			i += ft_strlen(tmp->value);
		ft_lexadd_back(&lex, tmp);
	}
	tmp = creat_new_node(input, i, 1);
	if (!tmp)
		return (ft_lexclear(&lex, free), NULL);
	ft_lexadd_back(&lex, tmp);
	return (lex);
}

/*
int	main(void)
{
	t_lexer *lex = lexer("               echo         |         'wc'");
	t_lexer *tmp = lex;
	
	while (tmp)
	{
		printf("%s : ", tmp->value);
		print_token_type(tmp->type);
		tmp = tmp->next;
	}
	ft_lexclear(&lex, free);
	return (0);
} */
