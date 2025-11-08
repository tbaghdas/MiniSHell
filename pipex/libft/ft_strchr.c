/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:51:20 by ikiriush          #+#    #+#             */
/*   Updated: 2025/01/26 23:51:22 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	i = 0;
	cc = c + 0;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		else
			i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}
