/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 23:41:26 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/10 10:54:15 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tokens(t_shell *sh)
{
	t_token	*tok_cur;

	tok_cur = sh->tok;
	while (tok_cur != NULL)
	{
		printf("TOKEN: %u ", tok_cur->type);
		if (tok_cur->type == 0)
			printf("CONTENT: %s\n", tok_cur->content);
		else
			printf("\n");
		tok_cur = tok_cur->next;
	}
}

int	lexer(char *line, t_shell *sh, t_qstate *qs)
{
	size_t	i;
	t_token	*tok_cur;
	int		len;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]) && *qs == NONE)
			i++;
		if (is_op_start(line[i]))
		{
			len = op_len(&line[i]);
			mint_op_token(line, &sh->tok, &i, len);
			continue ;
		}
		else if (line[i] && !is_op_start(line[i]))
			word_start(line, qs, &sh->tok, &i);
		if (!line[i])
			break ;
	}
	tok_cur = sh->tok;
	if (*qs != NONE)
		return (syntax_errorer_quotes(*qs, sh), 1);
	return (0);
}
