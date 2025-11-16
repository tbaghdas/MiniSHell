/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:56:17 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/16 02:17:54 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	qstate_updater(char c, t_qstate *qs)
{
	if (*qs == QS_NONE)
	{
		if (c == '\'')
			*qs = QS_SINGLE;
		else if (c == '\"')
			*qs = QS_DOUBLE;
	}
	else if (*qs == QS_SINGLE && c == '\'')
		*qs = QS_NONE;
	else if (*qs == QS_DOUBLE && c == '\"')
		*qs = QS_NONE;
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

int	is_escaping(t_qstate qs, char c)
{
	if (qs == QS_NONE)
		return (1);
	if (qs == QS_SINGLE)
		return (0);
	return (c == '$' || c == '"' || c == '\\');
}


