/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:45:54 by ikiriush          #+#    #+#             */
/*   Updated: 2025/01/28 17:45:56 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned char	i;
	char			*ptr;

	if (s[0] == '\0' || len == 0 || start > ft_strlen(s))
	{
		ptr = ((char *)malloc(1));
		if (!ptr)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	if (start + len <= (ft_strlen(s)))
		ptr = (char *)malloc((len + 1) * sizeof(char));
	if (start + len > (ft_strlen(s)))
		ptr = (char *)malloc((ft_strlen(s) - start + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return ((char *)ptr);
}
