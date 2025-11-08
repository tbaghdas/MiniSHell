/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:17:07 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/01/24 22:27:46 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dest == src || !n)
		return (dest);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (n--)
	{
		*d = *s++;
		d++;
	}
	return (dest);
}
