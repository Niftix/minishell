/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:08:03 by vcucuiet          #+#    #+#             */
/*   Updated: 2026/02/08 14:43:17 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprintf(t_list *lst, char format)
{
	char	*str;

	str = ft_strdup("%s\n");
	str[1] = format;
	if (!lst)
		return ;
	while (lst)
	{
		ft_printf(str, lst->content);
		lst = lst->next;
	}
}
