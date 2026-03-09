/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcucuiet <vcucuiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:15:06 by vcucuiet          #+#    #+#             */
/*   Updated: 2025/11/20 00:47:47 by vcucuiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lres;
	t_list	*l_node;
	void	*l_content;

	if (!lst || !f)
		return (NULL);
	lres = NULL;
	while (lst)
	{
		l_content = f(lst->content);
		if (!l_content)
			return (ft_lstclear(&lres, del), NULL);
		l_node = ft_lstnew(l_content);
		if (!l_node)
		{
			del(l_content);
			ft_lstclear(&lres, del);
			return (NULL);
		}
		ft_lstadd_back(&lres, l_node);
		lst = lst->next;
	}
	return (lres);
}
