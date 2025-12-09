/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:11:19 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/09 17:34:44 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		size;
	char	*s;

	if (src == NULL)
	{
		return (NULL);
	}
	size = 0;
	i = 0;
	while (src[i++])
		size++;
	s = (char *) malloc(size + 1);
	if (s == NULL)
		return (NULL);
	i = -1;
	while (src[++i])
		i[s] = i[src];
	i[s] = '\0';
	return (s);
}
