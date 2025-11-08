/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 23:40:27 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/02/15 15:52:21 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;
	void	*new_cont;

	if (!lst || !f || !del)
		return (NULL);
	new_cont = NULL;
	new_list = NULL;
	while (lst)
	{
		new_cont = f(lst -> content);
		node = ft_lstnew(new_cont);
		if (!node)
		{
			ft_lstclear(&new_list, del);
			del(new_cont);
			return (NULL);
		}
		ft_lstadd_back(&new_list, node);
		lst = lst -> next;
	}
	return (new_list);
}
