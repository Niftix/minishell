/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_var_cleaner.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:11:14 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/25 18:20:19 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATIC_VAR_CLEANER_H
# define STATIC_VAR_CLEANER_H
# include <unistd.h>

ssize_t	lex_set_buf(char *buf, char *input, size_t *idx);
char	**exp_chr(char *str, char **env, size_t idx, int exit_status);
char	*exp_extract_var(char *str, char **env, size_t *idx, int exit_status);

#endif