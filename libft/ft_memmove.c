/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:25:49 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/02/07 00:08:16 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst <= src || dst >= src + len)
		return (ft_memcpy(dst, src, len));
	while (len--)
		len[(unsigned char *)dst] = len[(unsigned char *)src];
	return (dst);
}
