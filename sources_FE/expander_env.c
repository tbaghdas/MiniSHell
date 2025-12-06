/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 02:38:29 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/06 01:09:06 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_extractor(char *line, char *buf, int *i, int *j)
{
	int		start;
	char	*value;
	char	*buf2;
	int		len;

	start = ++(*i);
	buf2 = NULL;
	while (line && line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	len = *i - start;
	if (len > 0)
	{
		buf2 = ft_substr(line, start, len);
		if (!buf2)
			return (1);
	}
	value = getenv(buf2);
	if (value)
	{
		start = 0;
		while (value[start])
			buf[(*j)++] = value[start++];
	}
	free(buf2);
	return (0);
}
