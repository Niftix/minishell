/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:17:16 by mville            #+#    #+#             */
/*   Updated: 2026/05/20 19:03:54 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"
# include "expand.h"
# include "wildcard.h"

/* PARSER->AST.C */
t_ast			*create_ast_node(t_ast_type type);
t_redirect		*redirect_new(t_redirect_type type, char *target,
					int fd_target);
void			redirect_add_end(t_redirect **lst, t_redirect *new);
void			ast_free(t_ast *ast);

/* PARSER->AST_REDIRECTION.C */
int				redirect_checker(t_token type);
t_redirect_type	token_to_redir(t_token type);
int				parse_one_redirect(t_lexer **cur, t_redirect **list,
					t_shell *shell);

/* PARSER->PARSER_CMD.C */
t_ast			*parse_simple_cmd(t_lexer **cur, t_shell *shell);
t_ast			*parse_cmd(t_lexer **cur, t_shell *shell);
int				add_word_to_cmd(t_ast *node, t_lexer *cur, t_shell *shell,
					int *nb_args);

/* PARSER->PARSER.C */
t_ast			*parse_and_or(t_lexer **cur, t_shell *shell);
t_ast			*check_parse(t_lexer *lex, t_shell *shell);
void			parser_put_error(t_lexer *lex);
void			error_ambiguous_redirect(char *value, t_shell *shell);

/* PARSER->HD_RESOLVE.C */
void			put_hd_none_line_error(char *name);
int				read_hd(t_redirect *redir, t_shell *shell);
int				hd_resolve(t_ast *ast, t_shell *shell);
int				resolve_token_error_with_hd(t_lexer *lex, t_shell *shell);
int				hd_fail(t_redirect *redir, char *name);
void			sigint_hd(int sig);
int				check_quote(t_redirect *redir);
char			*create_hd(t_redirect *redir);

/* PARSER->HD_UTILS.C */
char			*remove_quote(char *str);
char			*add_res(char *res, char *str);
int				write_line_hd(t_redirect *redir, t_shell *shell,
					char *line, int exp);
int				close_hd(t_redirect *redir, char *name);

#endif
