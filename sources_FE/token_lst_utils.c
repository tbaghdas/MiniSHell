/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:11:34 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/17 00:21:47 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *tok_lst_new(t_toktyp type, char *content)
{
	t_token	*new_node;
	
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup(content);
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	tok_lstadd_back(t_token **lst, t_token *new_node)
{
	t_token	*buf;

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

void	tok_lstclear(t_token **lst, void (*del)(void*))
{
	t_token	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if (del)
			del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}