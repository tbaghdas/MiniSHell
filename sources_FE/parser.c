/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:32:24 by ilya              #+#    #+#             */
/*   Updated: 2025/11/24 01:24:55 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int redirs_errors(t_token *tok_head)
{
	
}












void	parser(t_token *tok_head)
{
	int	ctr;

	ctr = 0;
	while(tok_head->next)
	{
		if (tok_head->type != TOK_WORD)
		{
			ctr++;
			if (ctr == 1 && tok_head->type == TOK_PIPE)
				syntax_errorer(tok_head->content);
			else if (redirs_error(tok_head) == 1);
				
			syntax_errorer(tok_head->content);
	}
}