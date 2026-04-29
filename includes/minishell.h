/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:37:12 by mville            #+#    #+#             */
/*   Updated: 2026/04/25 18:12:37 by vcucuiet         ###   ########.fr       */
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
# include "libft.h"

extern volatile sig_atomic_t	g_status;

typedef struct s_input_stash
{
	char	*stash;
	size_t	idx;
}	t_input_stash;

typedef struct s_shell
{
	char			**env;
	int				status_exit;
	int				run;
	int				in_pipe;
	int				stdin_backup;
	int				stdout_backup;
	pid_t			last_pid;
	char			*current_input;
	t_input_stash	input_stash;
	struct s_lexer	*t_current_lexer;
	struct s_ast	*t_current_ast;
}	t_shell;

typedef enum e_ast_type
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_GROUP,
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
	int					fd;
	int					fd_target;
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
int		check_if_shlvl_exist(t_shell *shell);
int		check_if_pwd_exist(t_shell *shell);

/* UTILS->FREE.C */
void	ft_free_tab(char **res);

/* UTILS->READLINE_UTILS.C */
char	*get_input(t_shell *shell);
char	*get_stash_line(t_input_stash *input_stash);
char	*check_multi_line(t_input_stash *input_stash, char *input);
void	clean_stash(t_input_stash *input_stash);
void	clean_loop(t_shell *shell);
void	free_shell(t_shell *shell);
void	child_exit(t_shell *shell, int status);

/* UTILS->CLEAN_STATIC_VAR.C */

void	clean_static_var(void);

/* UTILS->SIGNAL_UTILS.C */
void	signal_init(void);

/* EXPAND */

char	**expand(char *str, char **env, int exit_status);

/* EXEC->EXEC.C */
int		ast_dispatch(t_shell *shell, t_ast *ast);

/* EXEC->EXEC_CMD.C */
int		exec_cmd(t_shell *shell, t_ast *ast);
void	exec_fork_child(t_shell *shell, t_ast *ast);

/* EXEC->EXEC_PIPE.C */
int		exec_pipe(t_shell *shell, t_ast *ast);
void	left_pipe_writer(t_shell *shell, t_ast *ast, int *fd);
void	right_pipe_reader(t_shell *shell, t_ast *ast, int *fd);

/* EXEC->EXEC_AND_OR.C */
int		exec_and(t_shell *shell, t_ast *ast);
int		exec_or(t_shell *shell, t_ast *ast);

/* EXEC->EXEC_UTILS.C */
int		check_builtins(char *cmd);
int		fd_save(t_shell *shell);
void	fd_recovery(t_shell *shell);
void	gest_signal(void);
int		is_valid_id(char *s);
int		exit_is_num(char *s);
int		cd_chdir(char *dir);
char	*find_home(t_shell *shell);
int		update_env(t_shell *shell, char *old_pwd, char *new_pwd);

/* EXEC->EXEC_REDIR.C */
int		all_redirects(t_redirect *redirects);

/* EXEC->EXEC_GROUP.C */
int		exec_group(t_shell *shell, t_ast *ast);

/* EXEC->BUILD_ENV.C */
char	**build_exec_env(t_shell *shell);

/* EXEC->EXEC_CORE_BLT.C */
int		exec_builtins(t_shell *shell, t_ast *ast);

/* BUILTINS */
int		blt_cd(t_shell *shell, t_ast *ast);
int		blt_echo(t_shell *shell, t_ast *ast);
int		blt_env(t_shell *shell, t_ast *ast);
int		blt_exit(t_shell *shell, t_ast *ast);
int		blt_exit_num_error(char *arg);
int		blt_exit_parse_status(char *str);
int		blt_export(t_shell *shell, t_ast *ast);
int		blt_pwd(void);
int		blt_unset(t_shell *shell, t_ast *ast);
void	no_arg_print_export(t_shell *shell);
int		check_format_is_valid(char *s);

/* EXEC->RESOLVE_PATH.C */
char	*resolve_cmd_path(t_shell *shell, t_ast *ast);
int		check_if_directory(char *path);

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
