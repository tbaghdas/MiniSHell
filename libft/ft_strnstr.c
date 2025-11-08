/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:07:19 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/02/13 21:36:00 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_needle;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	len_needle = ft_strlen(needle);
	while (haystack[i] && i < len)
	{
		while (haystack[i] != needle[0] && haystack[i] && i < len)
			i++;
		if (len < len_needle + i || len_needle > len)
			return (NULL);
		if (!ft_strncmp(&haystack[i], needle, len_needle))
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
