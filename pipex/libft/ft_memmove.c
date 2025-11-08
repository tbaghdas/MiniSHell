/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:36:54 by ikiriush          #+#    #+#             */
/*   Updated: 2025/02/16 15:36:56 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return (dst);
	if (len == 0 && (dst == NULL || src == NULL))
		return (NULL);
	if (len != 0 && dst == NULL && src == NULL)
		return (NULL);
	if (src > dst)
	{
		while (i++ < len)
			((unsigned char *)dst)[i - 1] = ((unsigned char *)src)[i - 1];
	}
	else
	{
		while (len-- > 0)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
	}
	return (dst);
}
