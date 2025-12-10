/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 02:38:29 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/10 04:14:11 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	legit(char c)
{
	return (ft_isalnum(c) || c == '_');
}

void	env_extractor(char **pline, char **pbuf, t_shell *sh)
{
	char	*line;
	char	*buf;
	char	*start;
	char	*value;	
	char	*name;

	(*pline)++;
	line = *pline;
	buf = *pbuf;
	start = line;
	while (*line && legit(*line))
		line++;
	if (line == start)
		return ;
	name = ft_substr(start, 0, line - start);
	if (!name)
		fatal_error("malloc", sh);
	value = ft_getenv(name, sh->env);
	while (value && *value)
		*buf++ = *value++;
	*buf = '\0';
	*pline = line;
	*pbuf = buf;
	free(name);
}
