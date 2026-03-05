/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:24:52 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/05 16:47:55 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"

typedef struct s_token
{
	int	word;
	int	in;
	int	out;
	int	here_doc;
	int	append_out;
	int	pipe;
	int	is_and;
	int	is_or;
}			t_token_type;

typedef	struct s_lexer
{
	t_token_type	type;
	char			*value;
	t_lexer			*next;
}			t_lexer;

t_lexer	*ft_lexnew(void *value);
int		ft_lexadd_back(t_lexer **lst, t_lexer *new);
void	ft_lexclear(t_lexer **lst, void (*del)(void *));

#endif
