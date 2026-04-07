/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:37:12 by mville            #+#    #+#             */
/*   Updated: 2026/04/06 11:30:07 by vcucuiet         ###   ########.fr       */
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
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char	**env;
	int		status_exit;
	int		run;
	int		in_pipe;
	int		stdin_backup;
	int		stdout_backup;
	pid_t	last_pid;
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

/* EXPAND */

char	**expand(char *str, char **env);

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
int		fd_save(t_shell *shell);
void	fd_recovery(t_shell *shell);
void	gest_signal(void);
int		is_valid_id(char *s);
char	*find_home(t_shell *shell);
int		update_env(t_shell *shell, char *old_pwd, char *new_pwd);

/* EXEC->EXEC_REDIR.C */
int		all_redirects(t_redirect *redirects);

/* EXEC->EXEC_SUBSHELL.C */
int		exec_subshell(t_shell *shell, t_ast *ast);

/* BUILTINS->EXEC_BUILTINS.C */
int		exec_builtins(t_shell *shell, t_ast *ast);

/* BUILTINS->BUILTINS.C */
int		builtin_echo(t_ast *ast);
int		builtin_pwd(void);
int		builtin_cd(t_shell *shell, t_ast *ast);
int		builtin_env(t_shell *shell);
int		builtin_exit(t_shell *shell, t_ast *ast);

/* BUILTINS->BUILTIN_EXPORT.C */
int		builtin_export(t_shell *shell, t_ast *ast);

/* BUILTINS->BUILTIN_UNSET.C */
int		builtin_unset(t_shell *shell, t_ast *ast);

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
int		ft_atoi(const char *str);

#endif