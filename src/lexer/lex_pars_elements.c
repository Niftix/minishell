/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 20:43:27 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/15 20:07:20 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int lex_pars_elements(t_lexer *prev, t_lexer *now) // CONTINUE FOR ALL TOPKEN TYPE
{
    if (now->type == TOKEN_IN || now->type == TOKEN_OUT
        || now->type == TOKEN_APPEND_OUT || now->type == TOKEN_HERE_DOC)
        return (valid_redirect(now));
}
