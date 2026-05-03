
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 13:10:00 by mville            #+#    #+#             */
/*   Updated: 2026/05/03 13:10:00 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

typedef struct s_wildcard
{
	int	i_pattern;
	int	i_file;
	int	last_star;
	int	save_file;
}	t_wildcard;

int		find_match(char *pattern, char *filename);
char	**wildcard_core(char *str);
char	**return_str(char *str);
char	**add_file(char **res, char *name);

#endif
