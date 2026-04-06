/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:02:33 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/06 18:42:34 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "libft.h"

char	**expand(char *str, char **env, int exit_status);
char	*exp_chr_var_and_exp(char *str, char **env, size_t *idx);
int		exp_is_var_sep(char c);
int		exp_is_specifique_case(char *str, size_t idx);
char	*exp_specifique_case_var(char *str, size_t *idx, int exit_status);
size_t	exp_skip_tab_space_nl(char *str, size_t start);
int		is_ifs(char c);
char	*exp_chose_var(char *str, char **env, size_t *idx, int exit_status);
char	*exp_extract_none_var(char *str, size_t start, size_t end);

#endif