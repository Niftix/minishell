/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 20:07:59 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/05/01 17:50:12 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	lex_print_token_error(t_token token, int check)
{
	if (check == 2)
		return (ft_putstr_fd("'newline'\n", 2));
	if (token == TOKEN_IN)
		return (ft_putstr_fd("'<'\n", 2));
	if (token == TOKEN_OUT)
		return (ft_putstr_fd("'>'\n", 2));
	if (token == TOKEN_OR)
		return (ft_putstr_fd("'||'\n", 2));
	if (token == TOKEN_AND)
		return (ft_putstr_fd("'&&'\n", 2));
	if (token == TOKEN_LPAREN)
		return (ft_putstr_fd("'('\n", 2));
	if (token == TOKEN_RPAREN)
		return (ft_putstr_fd("')'\n", 2));
	if (token == TOKEN_PIPE)
		return (ft_putstr_fd("'|'\n", 2));
	if (token == TOKEN_HERE_DOC)
		return (ft_putstr_fd("'<<'\n", 2));
	if (token == TOKEN_APPEND_OUT)
		return (ft_putstr_fd("'>>'\n", 2));
}

static int	lex_pars_put_error(t_token token, int check)
{
	char	*error;

	if (check == 3)
		return (0);
	error = ft_strdup("minishell: syntax error near unexpected token ");
	ft_putstr_fd(error, 2);
	free(error);
	lex_print_token_error(token, check);
	return (0);
}

static t_lexer	*cpy_hd_until_error(t_lexer *res, t_lexer *lexer, t_lexer *end)
{
	while (lexer != end)
	{
		if (lexer->type == TOKEN_HERE_DOC && lexer->next->type == TOKEN_WORD)
		{
			if (lex_lexadd_back(&res, lex_cpy_node(lexer)))
				return (lex_lexclear(&res, free), NULL);
			lexer = lexer->next;
			if (lex_lexadd_back(&res, lex_cpy_node(lexer)))
				return (free(res), NULL);
		}
		lexer = lexer->next;
	}
	return (res);
}

static t_lexer	*lex_pars_error(t_lexer *tmp, t_lexer *lex, int check)
{
	t_lexer	*tmp_lex;

	tmp_lex = lex;
	lex = malloc(sizeof(t_lexer));
	if (!lex)
		return (NULL);
	lex->next = NULL;
	lex->value = NULL;
	if (check == -1)
	{
		ft_putstr_fd("minishell: maximum here_document count exceeded\n", 2);
		return (lex->type = ERROR_MAX_HD, lex_lexclear(&tmp_lex, free), lex);
	}
	lex_pars_put_error(tmp->type, check);
	lex->type = TOKEN_ERROR;
	lex = cpy_hd_until_error(lex, tmp_lex, tmp);
	lex_lexclear(&tmp_lex, free);
	return (lex);
}

t_lexer	*lex_pars(t_lexer *lex, int *status_exit)
{
	t_lexer	*tmp;
	t_lexer	*prev;
	int		check;
	int		nb_hd;

	prev = NULL;
	tmp = lex;
	nb_hd = 0;
	while (tmp->type != TOKEN_EOF)
	{
		if (tmp->type == TOKEN_HERE_DOC)
			nb_hd++;
		if (nb_hd > 16)
			return (lex_pars_error(tmp, lex, -1));
		check = lex_pars_elements(lex, prev, tmp);
		if (check)
			return (lex_pars_error(tmp, lex, check));
		prev = tmp;
		tmp = tmp->next;
	}
	if (lex->type == TOKEN_ERROR)
		*status_exit = 2;
	return (lex);
}
