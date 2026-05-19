/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:50:58 by mville            #+#    #+#             */
/*   Updated: 2026/05/19 10:51:00 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

typedef struct s_wildcard
{
	int	j;
	int	i;
	int	last_star;
	int	save_file;
}	t_wildcard;

int		find_match(char *pattern, char *filename);
char	**wildcard_core(char *str);
char	**return_str(char *str);
char	**add_file(char **res, char *name);

#endif
