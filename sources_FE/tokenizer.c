/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:02:40 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/29 20:00:51 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	word_start(char *line, t_qstate *qs, t_token **tok_head, size_t *i)
{
	size_t	init;

	init = *i;
	while (line[*i])
	{
		if (line[*i + 1] && line[*i] == '\\' && is_escaping(*qs, line[*i + 1]))
			(*i)++;
		else if (line[*i] == '\'' || line[*i] == '\"')
			qstate_updater(line[*i], qs);
		else if ((*qs == QS_NONE) && (ft_isspace(line[*i]) || is_op_start(line[*i])))
		{
			word_end(line, tok_head, *i, init);
			return ;
		}
		(*i)++;
	}
	word_end(line, tok_head, *i, init);
}

void	mint_op_token(char* line, t_token **tok_head, size_t* i, int len)
{
	t_token *new_node;

	new_node = NULL;
	if (len == 1)
	{
		if (line[*i] == '|')
			new_node = tok_lst_new(PIPE, "|");
		else if (line[*i] == '<')
			new_node = tok_lst_new(REDIR_IN, "<");
		else if (line[*i] == '>')
			new_node = tok_lst_new(REDIR_OUT, ">");
		else if (line[*i] == '\n')
			new_node = tok_lst_new(NEW_LINE, "newline");
		(*i)++;
	}
	else if (line[*i] == '<')
		new_node = tok_lst_new(HEREDOC, "<<");
	else if (line[*i] == '>')
		new_node = tok_lst_new(REDIR_APP, ">>");
	if (len == 2)
		(*i) += 2;
	tok_lstadd_back(tok_head, new_node);
}

void	word_end(char* line, t_token **tok_head, size_t i, size_t init)
{
	size_t size;
	t_token	*new_node;
	char* buf;
	
	size = i - init;
	buf = malloc((size + 1) * sizeof(char));
	ft_memcpy(buf, &line[init], size);
	buf[size] = '\0';
	new_node = tok_lst_new(WORD, buf);
	tok_lstadd_back(tok_head, new_node);
	free(buf);
}

