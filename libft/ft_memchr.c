/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:07:59 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/02/12 00:01:03 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	c = (unsigned char)c;
	str = (unsigned char *)s;
	while (i < n && (unsigned char)(i[str]) != c)
		i++;
	if (i == n)
		return (NULL);
	return ((void *)(&str[i]));
}
