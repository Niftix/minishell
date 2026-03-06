/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:37:12 by mville            #+#    #+#             */
/*   Updated: 2026/03/06 14:18:36 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char	**env;
	int		status_exit;
	int		run;
}	t_shell;

typedef enum e_ast_type
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR
}	t_ast_type;

typedef enum e_redirect_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*target;
	struct s_redirect		*next;
}	t_redirect;

typedef struct s_ast
{
	t_ast_type		type;
	char			**args_cmd;
	t_redirect			*redirects;
	struct s_node	*left;
	struct s_node	*right;
}	t_ast;                                              

/* UTILS->INITIALIZER.C */
int		shell_init(t_shell *shell, char **envp);

/* UTILS->FREE.C */
void	ft_free_tab(char **res);

/* UTILS->READLINE_UTILS.C */
char	*get_input(t_shell *shell);
void	free_and_clean_history(t_shell *shell);

/* UTILS->SIGNAL_UTILS.C */
void	signal_init(void);

#endif
