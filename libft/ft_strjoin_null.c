/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_null.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 00:14:55 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/11 00:18:34 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_null(char const *s1, char const *s2)
{
	char	*str;
	size_t	count;
	int		i;

	count = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = (char *) malloc (count * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (s1 != NULL)
	{
		while (*s1)
			str[i++] = *s1++;
	}
	if (s2 != NULL)
	{
		while (*s2)
			str[i++] = *s2++;
	}
	str[i] = '\0';
	return (str);
}
