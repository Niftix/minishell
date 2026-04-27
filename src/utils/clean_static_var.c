/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_static_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:53:48 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/25 18:29:29 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "static_var_cleaner.h"

void	clean_static_var(void)
{
	lex_set_buf(NULL, NULL, NULL);
	exp_chr(NULL, NULL, 0, 0);
	exp_extract_var(NULL, NULL, NULL, 0);
}
