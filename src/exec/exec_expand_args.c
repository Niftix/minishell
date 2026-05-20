/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expand_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 07:37:34 by mville            #+#    #+#             */
/*   Updated: 2026/05/20 08:27:55 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**expand_and_wildcard(char *word, t_shell *shell)
{
	char	*tmp;
	char	**new_words;
	char	**wildcard_words;

	tmp = ft_strdup(word);
	if (!tmp)
		return (NULL);
	new_words = expand(tmp, shell->env, shell->status_exit);
	if (!new_words)
		return (NULL);
	if (!new_words[0] || new_words[1])
		return (new_words);
	wildcard_words = wildcard_core(new_words[0]);
	ft_free_tab(new_words);
	return (wildcard_words);
}

char	**join_args(char **args_cmd, char **new_words, int *count)
{
	char	**args_new;
	int		nb_words;
	int		i;

	nb_words = 0;
	while (new_words[nb_words])
		nb_words++;
	args_new = ft_realloc(args_cmd, sizeof(char *) * (*count + 1),
			sizeof(char *) * (*count + nb_words + 1));
	if (!args_new)
		return (ft_free_tab(new_words), NULL);
	i = 0;
	while (new_words[i])
	{
		args_new[(*count)++] = remove_quote(new_words[i]);
		free(new_words[i]);
		i++;
	}
	args_new[*count] = NULL;
	free(new_words);
	return (args_new);
}

char	**expand_cmd_args(char **args_brut, t_shell *shell)
{
	char	**args;
	char	**new_words;
	int		i;
	int		count;

	args = malloc(sizeof(char *));
	if (!args)
		return (NULL);
	args[0] = NULL;
	i = 0;
	count = 0;
	while (args_brut && args_brut[i])
	{
		new_words = expand_and_wildcard(args_brut[i], shell);
		if (!new_words)
			return (ft_free_tab(args), NULL);
		args = join_args(args, new_words, &count);
		if (!args)
			return (NULL);
		i++;
	}
	return (args);
}

int	expand_ast_args(t_shell *shell, t_ast *ast)
{
	char	**expanded;

	expanded = expand_cmd_args(ast->args_cmd, shell);
	if (!expanded)
		return (1);
	ft_free_tab(ast->args_cmd);
	ast->args_cmd = expanded;
	return (0);
}
