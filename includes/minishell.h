/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:37:12 by mville            #+#    #+#             */
/*   Updated: 2026/03/10 11:39:47 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char	**env;
	int		status_exit;
	int		run;
	int  in_pipe;
 int stdin_backup;
 int stdout_backup;
 pid_t last_pid;
}	t_shell;

typedef enum e_ast_type
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_SUBSHELL,
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
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_ast
{
	t_ast_type		type;
	char			**args_cmd;
	t_redirect		*redirects;
	struct s_ast	*left;
	struct s_ast	*right;
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

/* EXEC->EXEC.C */
int		ast_dispatch(t_shell *shell, t_ast *ast);

/* EXEC->EXEC_CMD.C */
int		exec_cmd(t_shell *shell, t_ast *ast);

/* EXEC->EXEC_PIPE.C */
int		exec_pipe(t_shell *shell, t_ast *ast);

/* EXEC->EXEC_AND_OR.C */
int		exec_and(t_shell *shell, t_ast *ast);
int		exec_or(t_shell *shell, t_ast *ast);

/* EXEC->EXEC_UTILS.C */
int		check_builtins(char *cmd);

/* EXEC->EXEC_BUILTINS.C */
int		exec_builtins(t_shell *shell, t_ast *ast);

/* EXEC->PATH.C */
char	*find_cmd_path(t_shell *shell, t_ast *ast);

/* LIBFT */
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);

#endif
