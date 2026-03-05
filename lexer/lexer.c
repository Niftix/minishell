/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:50:00 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/05 19:14:38 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		set_lex(t_lexer **lex, char **splited_input, int idx)
{
	char	*value;
	int		i;
	char	quote;
	

	i = 0;
	value = ft_strdup(splited_input[idx]);
	if (!value)
		return (-1);
	//continue the quote gestion
	if (ft_lexadd_back(lex, value))
		return (-1);
	return (0);
}

t_lexer	*lexer(char *input)
{
	t_lexer	*lex;
	char	**splited_in;
	size_t	i;
	int		check;

	i = -1;
	splited_in = ft_split(input, ' ');
	if (!splited_in)
		return (NULL);
	while (splited_in[++i])
	{
		check = set_lex(lex, splited_in, i);
		if (check > 0)
			i += check;
		if (check == -1)
			return (ft_lexclear(lex, free), NULL);
	}
	return (lex);
}
/* #include <stdio.h>

int	main(void)
{
	t_lexer *lex = lexer("echo 'salut'42");

	printf("val 1 :%s\n", lex->value);
	prtinf("val 2 :%s\n", lex->next->value);
	prtinf("val 3 :%s\n", lex->next->next);
	return (0);
}
 */