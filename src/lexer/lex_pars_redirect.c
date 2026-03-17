/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:41:49 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/03/15 20:40:48 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int valid_redirect(t_lexer *now)
{
    if (now->next->type == TOKEN_WORD)
        return (0);
    return (1);
}
