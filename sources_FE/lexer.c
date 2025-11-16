/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 23:41:26 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/17 02:37:43 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
// int main(int argc, char** argv)
{
	char	*line; 
	size_t		i;
	t_token		*tok_head;
	t_qstate	qs;
	
	line = readline("minishell> ");
	// (void)argc;
	// line = argv[1];
	qs = QS_NONE;
	tok_head = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' && qs == QS_NONE)
			i++;
		if (is_op_start(line[i]))
		{
			int len = op_len(&line[i]);
			mint_op_token(line, &tok_head, &i, len);
			continue;
		}
		else if (line[i] && !is_op_start(line[i]))
			word_start(line, &qs, &tok_head, &i);
		if (!line[i])
			break;
	}
	while (tok_head != NULL)
	{
		printf("TOKEN: %u ", tok_head->type);
		if (tok_head->type == 0)
			printf("CONTENT: %s\n", tok_head->content);
		else
			printf("\n");
		tok_head = tok_head->next;
	}
	free(line);
}
