/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 02:33:03 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/25 03:25:03 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipes(t_token *cur_tok)
{
	int	count;

	count = 0;
	while (cur_tok)
	{
		if (cur_tok->type == TOK_PIPE)
			count++;
		cur_tok = cur_tok->next;
	}
	return (count);
}

int	count_words_until_pipe(t_token *cur_tok)
{
	int	count;

	count = 0;
	while (cur_tok->type != TOK_PIPE)
	{
		if (cur_tok->type == TOK_WORD)
			count++;
		cur_tok = cur_tok->next;
	}
	return (count);
}

int first_pipe_checker(t_token *cur)
{
	if (cur->type == TOK_PIPE)
		return 1;
	return 0;
}

redir_handler(t_token **cur_tok, t_cmd **cmd)
{
	
}

int words_handler(t_token *cur_tok, t_cmd **cmd)
{
	int arr_size;
	int wordcount;
	int i;
	int j;

	arr_size = count_pipes(cur_tok);
	i = 0;
	j = 0;
	wordcount = count_words_until_pipe(cur_tok);
	(*cmd)->argv[i] = malloc((sizeof(char*) * wordcount) + 1);
	while (i < arr_size && cur_tok)
	{
		if (cur_tok->type == TOK_WORD)
			(*cmd)->argv[i][j++] = ft_strdup(cur_tok-> content);
		else if (cur_tok->type > TOK_WORD)
			redir_handler(&cur_tok, cmd);
		else if (cur_tok->type == TOK_PIPE)
			pipe_walker(&i, &j);
		cur_tok = cur_tok->next;
	}
}
