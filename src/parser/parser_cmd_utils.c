/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:13:44 by mville            #+#    #+#             */
/*   Updated: 2026/04/11 00:01:47 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**add_args(char **args, char **words, int *count)
{
	char	**new;
	int		i;

	i = 0;
	while (words[i])
		i++;
	new = ft_realloc(args, sizeof(char *) * (*count + 1),
			sizeof(char *) * (*count + i + 1));
	if (!new)
		return (ft_free_tab(words), NULL);
	i = 0;
	while (words[i])
	{
		if (words[i][0] != '\0')
			new[(*count)++] = remove_quote(words[i]);
		free(words[i]);
		i++;
	}
	new[*count] = NULL;
	free(words);
	return (new);
}

int	add_arg_cmd(t_ast *node, t_lexer *cur, t_shell *shell, int *count)
{
	char	**words;
	char	*tmp;

	tmp = ft_strdup(cur->value);
	words = expand(tmp, shell->env, shell->status_exit);
	if (!words)
		return (1);
	node->args_cmd = add_args(node->args_cmd, words, count);
	if (!node->args_cmd)
		return (1);
	return (0);
}
