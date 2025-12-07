/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:29:08 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/08 01:25:29 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser(t_token *tok, t_shell *sh)
{
	t_cmd	*cmd_cur;
	int		cleanup_required;

	cleanup_required = 0;
	cmd_cur = sh->cmd;
	while (tok)
	{
		if (tok->type != PIPE)
			if (all_tokens_handler(&tok, &cmd_cur, sh))
				return (1);
		if (!tok || tok->type == PIPE)
		{
			if (tok && (
					(tok->next && tok->next->type == PIPE)
					|| (!tok->next)))
				cleanup_required = 1;
			cmd_lstadd_back(&sh->cmd, cmd_cur);
			cmd_cur = NULL;
			if (cleanup_required == 1)
				return (syntax_errorer_redirs(tok->content, sh), 1);
			if (tok)
				tok = tok->next;
		}
	}
	return (0);
}
