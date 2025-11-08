/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:39:21 by ikiriush          #+#    #+#             */
/*   Updated: 2025/02/18 13:39:22 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*freer(t_list **lst, void **map, int beacon, void (*del)(void *))
{
	if (beacon == 0)
		free (*map);
	if (beacon == 1)
	{
		ft_lstclear(lst, del);
		free (*map);
	}
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*my_list;
	void	*map;

	if (!lst || !f || !del)
		return (NULL);
	map = f(lst->content);
	head = ft_lstnew(map);
	if (!head)
		return (freer(&head, &map, 0, del));
	my_list = head;
	lst = lst->next;
	while (lst)
	{
		map = f(lst->content);
		my_list->next = ft_lstnew(map);
		if (!my_list->next)
			return (freer(&head, &map, 1, del));
		my_list = my_list->next;
		lst = lst->next;
	}
	return (head);
}
