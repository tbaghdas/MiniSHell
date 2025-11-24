/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:32:24 by ilya              #+#    #+#             */
/*   Updated: 2025/11/25 03:05:17 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"














void	parser(t_token *tok_head, t_cmd **cmd)
{
	t_token	*cur_tok;
	
	cur_tok = tok_head;
	if (first_pipe_checker(cur_tok))
			syntax_errorer("|");
	words_handler(cur_tok, *cmd);
	//redirs_handler(cur_tok, *cmd);
}