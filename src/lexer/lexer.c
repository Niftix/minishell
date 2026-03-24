/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:50:00 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/24 16:47:06 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static size_t	lex_skip_tab_space_nl(char *input, size_t start)
{
	size_t	idx;

	idx = start;
	while (input[idx] && (input[idx] == '\t' || input[idx] == ' '
			|| input[idx] == '\n'))
		idx++;
	return (idx);
}

static size_t	lex_token_len(t_token token)
{
	if (token == TOKEN_AND || token == TOKEN_APPEND_OUT
		|| token == TOKEN_HERE_DOC || token == TOKEN_OR)
		return (2);
	return (1);
}

t_lexer	*lexer_creat(char *input, char *exec_name, int *exit_status)
{
	t_lexer	*lex;
	t_lexer	*tmp;
	size_t	i;
	size_t	input_len;

	if (!input)
		return (NULL);
	i = 0;
	lex = NULL;
	input_len = ft_strlen(input);
	while (i < input_len + 1)
	{
		i = lex_skip_tab_space_nl(input, i);
		tmp = lex_creat_new_node(input, i, 1);
		if (!tmp)
			return (lex_lexclear(&lex, free), NULL); // need malloc failed error
		if (tmp->type != TOKEN_WORD)
			i += lex_token_len(tmp->type);
		else
			i += ft_strlen(tmp->value);
		lex_lexadd_back(&lex, tmp);
	}
	return (lex_pars(lex, exec_name, exit_status));
}

/* int	main(int ac, char **av)
{
	t_lexer	*lex;
	t_lexer	*tmp;

	if (ac != 2)
		return (ft_putstr_fd("Error: Need only one cmd line\n", 2), 1);
	lex = lexer_creat(av[1], av[0]);
	tmp = lex;
	while (tmp)
	{
		printf("%s : ", tmp->value);
		lex_print_token_type(tmp->type);
		tmp = tmp->next;
	}
	lex_lexclear(&lex, free);
	return (0);
} */
