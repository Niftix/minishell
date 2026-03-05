/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:24:52 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/05 18:02:15 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"

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
}			t_token;

typedef	struct s_lexer
{
	t_token	type;
	char	*value;
	t_lexer	*next;
}			t_lexer;

t_lexer	*ft_lexnew(char *value);
int		ft_lexadd_back(t_lexer **lst, t_lexer *new);
void	ft_lexclear(t_lexer **lst, void (*del)(void *));

#endif
