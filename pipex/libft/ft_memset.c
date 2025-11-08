/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:23:55 by ikiriush          #+#    #+#             */
/*   Updated: 2025/01/23 13:24:02 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The memset() function writes len bytes of value c
(converted to an unsigned char) to the string b.*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	buc;

	i = 0;
	buc = (unsigned char)c;
	while (i < len)
	{
		((unsigned char *)b)[i] = buc;
		i++;
	}
	return (b);
}
