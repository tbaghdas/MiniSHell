/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 01:30:11 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/06 02:31:19 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_expander(char **line, t_shell *sh)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	buf = malloc(VAR_NAME_MAX * sizeof(char));
	if (!buf)
		fatal_error("malloc", sh);
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			if (env_extractor(*line, buf, &i, &j))
				fatal_error("malloc", sh);
			continue ;
		}
		buf[j++] = (*line)[i++];
	}
	buf[j] = '\0';
	free(*line);
	*line = ft_strdup(buf);
	free(buf);
	if (!*line)
		fatal_error("malloc", sh);
}
