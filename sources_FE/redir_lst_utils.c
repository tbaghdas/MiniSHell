/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:11:34 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/09 01:37:59 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*redir_lst_new(t_token *tok)
{
	t_redir	*new_node;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (NULL);
	new_node->type = tok->type;
	new_node->target = ft_strdup(tok->next->content);
	new_node->fd = -1;
	if (tok->type == HEREDOC)
	{
		if (tok->next && tok->next->content
			&& (ft_strchr(tok->next->content, '\'')
				|| ft_strchr(tok->next->content, '\"')))
			new_node->do_expand = 0;
		else
			new_node->do_expand = 1;
	}
	new_node->next = NULL;
	return (new_node);
}

void	redir_lstadd_back(t_redir **lst, t_redir *new_node)
{
	t_redir	*buf;

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

void	redir_lstclear(t_redir **lst, void (*del)(void*))
{
	t_redir	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if (del)
			del((*lst)->target);
		free(*lst);
		*lst = temp;
	}
}
