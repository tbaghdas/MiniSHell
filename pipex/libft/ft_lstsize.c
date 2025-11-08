/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:12:55 by ikiriush          #+#    #+#             */
/*   Updated: 2025/02/17 21:12:58 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	ctr;

	ctr = 1;
	if (!lst)
		return (0);
	if (lst && !lst->next)
		return (1);
	while (lst && lst->next)
	{
		ctr++;
		lst = lst->next;
	}
	return (ctr);
}
