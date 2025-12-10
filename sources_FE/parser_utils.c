/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 02:33:03 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/11 02:56:16 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_buffer_node(t_cmd **cmd)
{
	int		i;

	i = 0;
	while ((*cmd)->argv[i])
		free((*cmd)->argv[i++]);
	free((*cmd)->argv);
	if ((*cmd)->redirs)
	{
		if ((*cmd)->redirs->target)
			free((*cmd)->redirs->target);
		free((*cmd)->redirs);
	}
	free(*cmd);
}

static int	count_words_until_pipe(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == WORD)
			count++;
		// else if (tok->type != WORD)
		// 	count--;
		tok = tok->next;
	}
	if (count < 0)
		count = 0;
	return (count);
}

static int	redir_handler(t_token **tok, t_cmd **cmd_cur, t_shell *sh)
{
	t_redir	*redir_cur;

	redir_cur = (*cmd_cur)->redirs;
	if (!(*tok)->next)
		return (syntax_errorer_redirs("newline", sh), 1);
	else if ((*tok)->next->type == PIPE)
		return (syntax_errorer_redirs((*tok)->next->content, sh), 1);
	else if ((*tok)->next->type != WORD)
		return (syntax_errorer_redirs((*tok)->next->content, sh), 1);
	redir_cur = redir_lst_new(*tok);
	redir_lstadd_back(&(*cmd_cur)->redirs, redir_cur);
	*tok = (*tok)->next;
	return (0);
}

int	all_tokens_handler(t_token **tok, t_cmd **cmd_cur, t_shell *sh)
{
	int	ctr;

	ctr = count_words_until_pipe(*tok);
	*cmd_cur = cmd_lst_new();
	if (!(cmd_cur))
		fatal_error("malloc", sh);
	(*cmd_cur)->argv = malloc(sizeof(char *) * (ctr + 1));
	if (!((*cmd_cur)->argv))
		fatal_error("malloc", sh);
	(*cmd_cur)->argv[ctr] = NULL;
	ctr = 0;
	while (*tok && (*tok)->type != PIPE)
	{
		if ((*tok)->type == WORD)
		{
			(*cmd_cur)->argv[ctr++] = ft_strdup((*tok)->content);
			if (!(*cmd_cur)->argv)
				fatal_error("malloc", sh);
		}
		else
			if (redir_handler(tok, cmd_cur, sh))
				return (free_buffer_node(cmd_cur), 1);
		*tok = (*tok)->next;
	}
	return ((*cmd_cur)->argv[ctr] = NULL, 0);
}
