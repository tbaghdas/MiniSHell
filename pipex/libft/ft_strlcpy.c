/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:11:15 by ikiriush          #+#    #+#             */
/*   Updated: 2025/02/15 21:11:28 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	if (dstsize == 1 || src[0] == '\0')
	{
		dst[0] = '\0';
		return (src_len);
	}
	n = 0;
	while (src[n] != '\0' && (n < dstsize - 1))
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = '\0';
	return (src_len);
}
