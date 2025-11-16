/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 23:41:26 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/16 23:33:29 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char** argv)
{
	char	*line = argv[1];
	size_t		i;
	t_token		*tok_head;
	t_qstate	qs;
	
	(void)argc;
	
	qs = QS_NONE;
	tok_head = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' && qs == QS_NONE)
			i++;
		if (is_op_start(line[i]))
		{
			mint_op_token(&line[i], &tok_head, &i, op_len(&line[i]));
			continue;
		}
		else
			word_start(line, &qs, &tok_head, &i);
		if (line[i])
			i++;
	}
	while (tok_head->next != NULL)
	{
		printf("%u\n", tok_head->type);
		printf("%s\n", tok_head->content);
		tok_head = tok_head->next;
	}
}
