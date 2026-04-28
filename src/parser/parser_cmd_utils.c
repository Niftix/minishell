/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:13:44 by mville            #+#    #+#             */
/*   Updated: 2026/04/28 16:45:37 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**join_args(char **args_cmd, char **new_words, int *nb_args)
{
	char	**args_new;
	int		nb_words;
	int		i;

	nb_words = 0;
	while (new_words[nb_words])
		nb_words++;
	args_new = ft_realloc(args_cmd, sizeof(char *) * (*nb_args + 1),
			sizeof(char *) * (*nb_args + nb_words + 1));
	if (!args_new)
		return (ft_free_tab(new_words), NULL);
	i = 0;
	while (new_words[i])
	{
		args_new[(*nb_args)++] = remove_quote(new_words[i]);
		free(new_words[i]);
		i++;
	}
	args_new[*nb_args] = NULL;
	free(new_words);
	return (args_new);
}

int	add_word_to_cmd(t_ast *node, t_lexer *cur, t_shell *shell, int *nb_args)
{
	char	**new_words;
	char	*word;

	word = ft_strdup(cur->value);
	new_words = expand(word, shell->env, shell->status_exit);
	if (!new_words)
		return (1);
	node->args_cmd = join_args(node->args_cmd, new_words, nb_args);
	if (!node->args_cmd)
		return (1);
	return (0);
}
