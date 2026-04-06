/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:19:18 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/04/06 17:48:05 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	**expand(char *str, char **env, int exit_status);

int	main(int ac, char **av, char **env)
{
	char	*str = ft_strdup("salut $USER \"tu es la:&PWD\"  \'last_exit:$?\'");
	char	**exp = NULL;

	((void)ac, (void)av);
	exp = expand(str, env, 0);
	for (int i = 0; exp[i]; i++)
		printf("%s\n", exp[i]);
	ft_free2c(exp);
	return (0);
}
