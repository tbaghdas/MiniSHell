/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:13:03 by ikiriush          #+#    #+#             */
/*   Updated: 2025/01/27 00:13:05 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		buf;
	char	cc;

	i = 0;
	buf = -1;
	cc = c + 0;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
		{
			buf = i;
			i++;
		}
		else
			i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	if (buf != -1)
		return ((char *)&s[buf]);
	return (NULL);
}
