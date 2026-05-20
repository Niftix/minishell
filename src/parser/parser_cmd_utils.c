/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:13:44 by mville            #+#    #+#             */
/*   Updated: 2026/05/20 18:33:41 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_word_to_cmd(t_ast *node, t_lexer *cur, t_shell *shell, int *count)
{
	char	**args_new;

	(void)shell;
	args_new = ft_realloc(node->args_cmd, sizeof(char *) * (*count + 1),
			sizeof(char *) * (*count + 2));
	node->args_cmd = args_new;
	if (!args_new)
		return (1);
	node->args_cmd = args_new;
	node->args_cmd[*count] = ft_strdup(cur->value);
	if (!node->args_cmd[*count])
		return (1);
	(*count)++;
	node->args_cmd[*count] = NULL;
	return (0);
}
