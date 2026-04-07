/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:17:16 by mville            #+#    #+#             */
/*   Updated: 2026/04/07 13:55:24 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"
# include "expand.h"

/* PARSER->AST.C */
t_ast			*create_ast_node(t_ast_type type);
t_redirect		*redirect_new(t_redirect_type type, char *target);
void			redirect_add_end(t_redirect **lst, t_redirect *new);
void			ast_free(t_ast *ast);

/* PARSER->AST_REDIRECTION.C */
int				redirect_checker(t_token type);
int				cmd_token_checker(t_token type);
t_redirect_type	token_to_redir(t_token type);
int				parse_one_redirect(t_lexer **cur, t_redirect **list);

/* PARSER->PARSER_CMD.C */
t_ast			*parse_simple_cmd(t_lexer **cur, t_shell *shell);
t_ast			*parse_cmd(t_lexer **cur, t_shell *shell);

/* PARSER->PARSER.C */
t_ast			*parse_and_or(t_lexer **cur, t_shell *shell);
t_ast			*check_parse(t_lexer *lex, t_shell *shell);

/* PARSER->HD_RESOLVE.C */
char			*remove_quote(char *str);
int				read_hd(t_redirect *redir, t_shell *shell);
int				hd_resolve(t_ast *ast, t_shell *shell);

#endif
