/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 02:33:03 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/29 20:09:54 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_until_pipe_or_nl(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != PIPE && tok->type != NEW_LINE)
	{
		if (tok->type == WORD)
			count++;
		else if (tok->type != WORD)
			count--;
		tok = tok->next;
	}
	return (count);
}

void	redir_handler(t_token **tok, t_cmd **cmd)
{
	t_redir	*redir_cur;
	
	redir_cur = (*cmd)->redirs;
	if (!(*tok)->next)
		syntax_errorer("newline");
	else if ((*tok)->next->type == PIPE)
		syntax_errorer((*tok)->next->content);
	else if ((*tok)->next->type != WORD)
		syntax_errorer((*tok)->next->content);
	redir_cur = redir_lst_new(*tok);
	redir_lstadd_back(&(*cmd)->redirs, redir_cur);
	*tok = (*tok)->next;
	}

void	all_tokens_handler(t_token **tok, t_cmd **cmd)
{
	int wordcount;
	int i;
	
	wordcount = count_words_until_pipe_or_nl(*tok);
	i = 0;
	*cmd = cmd_lst_new();
	(*cmd)->argv = malloc(sizeof(char*) * (wordcount + 1));
	(*cmd)->argv[wordcount] = NULL;
	while (*tok && (*tok)->type != PIPE && (*tok)->type != NEW_LINE)
	{
		if ((*tok)->type == WORD)
		{
			(*cmd)->argv[i++] = ft_strdup((*tok)->content);
		}
		else
			redir_handler(tok, cmd);
		*tok = (*tok)->next;
	}
}

