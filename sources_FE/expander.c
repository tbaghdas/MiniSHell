/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 01:26:58 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/10 03:49:24 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander(t_shell *sh)
{
	handle_cmds(sh);
	handle_redirs(sh);
}

void	actual_expander(char **line, t_shell *sh, t_toktyp type)
{
	char		*buf;
	char		*s;
	char		*dst;

	s = *line;
	sh->qs = NONE;
	buf = malloc(VAR_NAME_MAX * sizeof(char));
	if (!buf)
		fatal_error("malloc", sh);
	dst = buf;
	while (*s)
	{
		if (quote_changes(*s, sh->qs))
			qstate_updater(*s++, &(sh)->qs);
		else if (expand_needed(s, sh->qs, type))
		{
			if (!exit_coder(&s, &dst, sh))
				env_extractor(&s, &dst, sh);
		}
		else
			*dst++ = *s++;
	}
	*dst = '\0';
	free(*line);
	*line = buf;
}
