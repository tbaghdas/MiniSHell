/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 01:30:11 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/10 02:53:02 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_expander(char **line, t_shell *sh)
{
	char	*src;
	char	*dst;
	char	*buf;

	src = *line;
	buf = malloc(VAR_NAME_MAX * sizeof(char));
	if (!buf)
		fatal_error("malloc", sh);
	dst = buf;
	while (*src)
	{
		if (*src == '$')
		{
			if (!exit_coder(&src, &dst, sh))
				env_extractor(&src, &dst, sh);
			continue ;
		}
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	free(*line);
	*line = buf;
}
