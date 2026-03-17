/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:24:52 by vcucuiet          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/03/17 14:39:41 by vcucuiet         ###   ########.fr       */
=======
/*   Updated: 2026/03/12 15:22:31 by vcucuiet         ###   ########.fr       */
>>>>>>> main
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
	TOKEN_EOF,
	TOKEN_ERROR,
}					t_token;

typedef struct s_lexer
{
	t_token			type;
	char			*value;
	struct s_lexer	*next;
}					t_lexer;

t_lexer	*lexer_creat(char *input, char *exec_name);

t_lexer	*lexer_creat(char *input);

t_token	lex_tokeniser(char *input, size_t *idx);
t_lexer	*lex_creat_new_node(char *input, size_t idx, int status);
char	*lex_set_value(char *input, size_t idx);
int		lex_lexadd_back(t_lexer **lst, t_lexer *new);
void	lex_lexclear(t_lexer **lst, void (*del)(void *));

t_lexer	*lex_pars(t_lexer *lex, char *exec_nameeeee);
int		lex_pars_elements(t_lexer *lexer, t_lexer *prev, t_lexer *now);

void	lex_print_token_type(t_token token); // debug ft

#endif
