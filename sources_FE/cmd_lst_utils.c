/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:11:34 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/25 01:31:22 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int word_counter(t_token *tok_head)
{
	int	ctr;
	
	ctr = 0;
	
	while(tok_head->next && tok_head->type == TOK_WORD)
	{
		ctr++;
	}
}


t_cmd *cmd_lst_new(t_redir *redirs, char *argv)
{
	t_token	*new_node;
	
	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->argv = ft_strdup(content);
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