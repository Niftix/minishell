/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:02:33 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/24 22:49:29 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "libft.h"

char	**expand(char *str, char **env, int exit_status);
char	*exp_cringe_dolars(char *str);
char	*exp_chr_var_and_exp(char *str, char **env, size_t *idx);
int		exp_is_var_sep(char c);
int		exp_is_specifique_case(char *str, size_t idx);
char	*exp_specifique_case_var(char *str, size_t *idx, int exit_status);
size_t	exp_skip_tab_space_nl(char *str, size_t start);
int		is_ifs(char c);
char	*exp_chose_var(char *str, char **env, size_t *idx, int exit_status);
char	*exp_extract_none_var(char *str, size_t start, size_t end);
char	*exp_var_append_to_last(char *dest, char *src);
char	**exp_verif_expand(char **var, int *len_var, int pose, int *need_new);
char	**exp_var_append_without_new_idx(char **res, int *r_len, char *var,
		int *need_new);
int		exp_calc_if_need_new_var(char c, int need_new, char *str, size_t idx);
void	exp_set_exp_extract_var(char *quote, char *str, size_t *idx);
char	exp_get_quote_state(char *str, size_t idx);

#endif