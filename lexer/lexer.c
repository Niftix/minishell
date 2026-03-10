/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:50:00 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/10 00:53:05 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

size_t	skip_tab_space_nl(char *input, int start)
{
	size_t	idx;

	idx = start;
	while (input[idx] && (input[idx] == '\t' || input[idx] == ' ' || input[idx] == '\n'))
		idx++;
	return (idx);
}

size_t	set_buf(char *buf, char *input, size_t *idx)
{
	size_t	i;
	int		in_q;
	char	quote;

	in_q = 0;
	quote = 'x';
	i = -1;
	while (++i < LEXER_BUF && input[*idx])
	{
		if (quote == 'x' && (input[*idx] == '\'' || input[*idx] == '\"'))
			(in_q++, quote = input[*idx]);
		else if (input[*idx] == quote)
			(in_q--, quote = 'x');
		if ((!in_q && input[*idx] == ' ') || (!in_q && tokeniser(input, idx) != TOKEN_WORD))
			return (*idx += 1, i);	
		buf[i] = input[*idx];
		*idx += 1;
	}
	return (i);
}

static char	*set_value(char *input, size_t idx)
{
	char	*val;
	char	*buf;
	int		t_cpy;
	ssize_t	val_len;

	val = NULL;
	val_len = 0;
	buf = malloc(sizeof(char) * (LEXER_BUF + 1));
	if (!buf)
		return (NULL);
	while(1)
	{
		t_cpy = set_buf(buf, input, &idx);
		buf[t_cpy] = '\0';
		val = ft_strdupcat(val, buf, &val_len, t_cpy);
		if (t_cpy != LEXER_BUF)
			break ;
	}
	free(buf);
	buf = NULL;
	return (val);
}

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
size_t	token_len(t_token token)
{
	if (token == TOKEN_AND || token == TOKEN_APPEND_OUT ||
		token == TOKEN_HERE_DOC || token == TOKEN_OR)
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
		if(!tmp)
			return (ft_lexclear(&lex, free), NULL); //need to handle malloc failed error
		if (tmp->type != TOKEN_WORD)
			i += token_len(tmp->type);
		else
			i += ft_strlen(tmp->value);
		ft_lexadd_back(&lex, tmp);
	}
	tmp = creat_new_node(input, i, 1);
		if(!tmp)
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
