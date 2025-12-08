/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 02:38:29 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/08 23:56:34 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	legit(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	env_extractor(char *line, char *buf, int *i, int *j)
{
	int		start;
	char	*value;
	char	*buf2;
	int		len;

	start = ++(*i);
	buf2 = NULL;
	while (line && line[*i] && legit(line[*i]))
		(*i)++;
	len = *i - start;
	if (len > 0)
	{
		buf2 = ft_substr(line, start, len);
		if (!buf2)
			return (1);
	}
	start = 0;
	if (buf2)
	{
		value = getenv(buf2);
		if (value)
			while (value[start])
				buf[(*j)++] = value[start++];
	}
	return (free(buf2), 0);
}
