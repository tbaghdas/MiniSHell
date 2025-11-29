/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:29:08 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/29 20:12:35 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	parser(t_token *tok, t_cmd **cmd)
{
	t_cmd	*cmd_cur;

	while (tok)
	{
		if (tok->type != PIPE && tok->type != NEW_LINE)
			all_tokens_handler(&tok, &cmd_cur);
		if (!tok || tok->type == PIPE || tok->type == NEW_LINE)
		{
			if (tok && (
				(tok->next && tok->next->type == PIPE) ||
				(tok->next && tok->next->type == NEW_LINE) ||
				(!tok->next)))
					syntax_errorer(tok->content);
			cmd_lstadd_back(cmd, cmd_cur);
			cmd_cur = NULL;
			if (tok)
				tok = tok->next;
		}
	}
}
