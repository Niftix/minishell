/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:24:52 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/10 14:44:49 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"
# include <stdio.h>
# ifndef LEXER_BUF
#  define LEXER_BUF 255
# endif

typedef enum e_token
{
	TOKEN_WORD,
	TOKEN_IN,
	TOKEN_OUT,
	TOKEN_HERE_DOC,
	TOKEN_APPEND_OUT,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
}			t_token;

typedef	struct s_lexer
{
	t_token			type;
	char			*value;
	struct s_lexer	*next;
}			t_lexer;

t_token	tokeniser(char *input, size_t *idx);
t_lexer	*creat_new_node(char *input, size_t idx, int status);
char	*set_value(char *input, size_t idx);
int		ft_lexadd_back(t_lexer **lst, t_lexer *new);
void	ft_lexclear(t_lexer **lst, void (*del)(void *));
void	print_token_type(t_token token);		//debug ft

#endif
