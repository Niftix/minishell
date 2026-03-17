/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 20:07:59 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/17 14:35:57 by vcucuiet         ###   ########.fr       */
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

static int	lex_pars_put_error(t_token token, int check, char *exec_name)
{
	char	*error;
	char	*ptr;

	error = ft_strdup(exec_name);
	if (!error)
		return (1);
	ptr = error;
	error = ft_strrchr(error, '/') + 1;
	error = ft_strjoin(error, ": syntax error near unexpected token ");
	if (!error)
		return (free(ptr), 1);
	free(ptr);
	ft_putstr_fd(error, 2);
	free(error);
	lex_print_token_error(token, check);
	return (0);
}

static t_lexer	*lex_pars_error(t_lexer *tmp, t_lexer *lex, int check,
		char *exec_name)
{
	lex_pars_put_error(tmp->type, check, exec_name);
	lex_lexclear(&lex, free);
	lex = malloc(sizeof(t_lexer));
	if (!lex)
		return (NULL);
	lex->next = NULL;
	lex->value = NULL;
	lex->type = TOKEN_ERROR;
	return (lex);
}

t_lexer	*lex_pars(t_lexer *lex, char *exec_name)
{
	t_lexer	*tmp;
	t_lexer	*prev;
	int		check;

	prev = NULL;
	tmp = lex;
	while (tmp->type != TOKEN_EOF)
	{
		check = lex_pars_elements(lex, prev, tmp);
		if (check)
			return (lex_pars_error(tmp, lex, check, exec_name));
		prev = tmp;
		tmp = tmp->next;
	}
	return (lex);
}
