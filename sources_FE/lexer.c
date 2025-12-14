/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 23:41:26 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/15 01:02:34 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer(char *line, t_shell *sh, t_qstate *qs)
{
	size_t	i;
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
	if (*qs != NONE)
		return (syntax_errorer_quotes(*qs, sh), 1);
	return (0);
}
