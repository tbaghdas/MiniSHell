/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:02:40 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/16 23:17:43 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_start(char *line, t_qstate *qs, t_token **tokhead, size_t *i)
{
	size_t	init;

	init = *i;
	while (line[*i])
	{
		if (line[*i + 1] && line[*i] == '\\' && is_escaping(*qs, line[*i + 1]))
			(*i)++;
		else if (line[*i] == '\'' || line[*i] == '\"')
			qstate_updater(line[*i], qs);
		else if ((*qs == QS_NONE) && (line[*i] == ' ' || is_op_start(line[*i])))
		{
			word_end(line, tokhead, *i, init);
			return ;
		}
		(*i)++;
	}
	word_end(line, tokhead, *i, init);
}

void	mint_op_token(char* line, t_token **tokhead, size_t* i, int len)
{
	char *buf;
	t_token *new_node;

	new_node = NULL;
	buf = malloc((len + 1) * sizeof(char));
	ft_memcpy(buf, &line[*i], len);
	if (len == 1)
	{
		if (ft_strncmp(buf, "|", 1))
			new_node = tok_lst_new(TOK_PIPE, buf);
		else if (ft_strncmp(buf, "<", 1))
			new_node = tok_lst_new(TOK_REDIR_IN, buf);
		else if (ft_strncmp(buf, ">", 1))
			new_node = tok_lst_new(TOK_REDIR_OUT, buf);
		(*i)++;
	}
	else if (ft_strncmp(buf, "<<", 1))
		new_node = tok_lst_new(TOK_HEREDOC, buf);
	else if (ft_strncmp(buf, ">>", 1))
		new_node = tok_lst_new(TOK_REDIR_APP, buf);
	if (len == 2)
		(*i) += 2;
	tok_lstadd_back(tokhead, new_node);
	free(buf);
}

void	word_end(char* line, t_token **tokhead, size_t i, size_t init)
{
	size_t size;
	t_token	*new_node;
	char* buf;
	
	size = i - init;
	buf = malloc((size + 1) * sizeof(char));
	ft_memcpy(buf, &line[init], size);
	new_node = tok_lst_new(TOK_WORD, buf);
	tok_lstadd_back(tokhead, new_node);
	free(buf);
}

