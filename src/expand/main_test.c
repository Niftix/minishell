/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:19:18 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/02 16:00:08 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	**expand(char *str, char **env);

int	main(int ac, char **av, char **env)
{
	char	*str = ft_strdup("$USER");
	char	**exp = NULL;

	((void)ac, (void)av);
	exp = expand(str, env);
	printf("%s\n", exp[0]);
	printf("%s\n", exp[1]);
	if (exp)
	{
		free(exp[0]);
		free(exp);
	}
}
