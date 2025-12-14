/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:11:34 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/11 05:15:53 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*cmd_lst_new(void)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->argv = NULL;
	new_node->redirs = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	cmd_lstadd_back(t_cmd **lst, t_cmd *new_node)
{
	t_cmd	*buf;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	buf = *lst;
	while (buf && buf->next)
		buf = buf->next;
	buf->next = new_node;
}

void	cmd_lstclear(t_cmd **lst, void (*del)(void*))
{
	t_cmd	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if (del)
			del((*lst)->argv);
		free(*lst);
		*lst = temp;
	}
}
