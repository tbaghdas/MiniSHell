/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 23:41:26 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/28 23:14:35 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer(char *line, t_token **tok_head, t_qstate *qs)
{
	size_t	i;
	// t_token	*tok_cur;
	
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' && *qs == QS_NONE)
			i++;
		if (is_op_start(line[i]))
		{
			int len = op_len(&line[i]);
			mint_op_token(line, tok_head, &i, len);
			continue;
		}
		else if (line[i] && !is_op_start(line[i]))
			word_start(line, qs, tok_head, &i);
		if (!line[i])
			break;
	}
	// tok_cur = *tok_head;
	// while (tok_cur != NULL)
	// {
	// 	printf("TOKEN: %u ", tok_cur->type);
	// 	if (tok_cur->type == 0)
	// 		printf("CONTENT: %s\n", tok_cur->content);
	// 	else
	// 		printf("\n");
	// 	tok_cur = tok_cur->next;
	// }
	free(line);
}
