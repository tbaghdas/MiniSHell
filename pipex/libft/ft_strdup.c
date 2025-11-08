/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:49:44 by ikiriush          #+#    #+#             */
/*   Updated: 2025/01/28 16:49:45 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*trgt;
	int		i;

	trgt = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!trgt)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		trgt[i] = s1[i];
		i++;
	}
	trgt[i] = '\0';
	return (trgt);
}
