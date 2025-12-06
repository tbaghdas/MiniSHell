/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:56:17 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/05 03:52:44 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	qstate_updater(char c, t_qstate *qs)
{
	if (*qs == NONE)
	{
		if (c == '\'')
			*qs = SINGLE;
		else if (c == '\"')
			*qs = DOUBLE;
	}
	else if (*qs == SINGLE && c == '\'')
		*qs = NONE;
	else if (*qs == DOUBLE && c == '\"')
		*qs = NONE;
}

int	is_op_start(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	op_len(char *s)
{
	if (s[0] == '>' && s[1] == '>')
		return (2);
	if (s[0] == '<' && s[1] == '<')
		return (2);
	return (1);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\r'
		|| c == '\t' || c == '\v' || c == '\n');
}
