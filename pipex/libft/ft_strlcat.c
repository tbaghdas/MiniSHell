/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:59:28 by ikiriush          #+#    #+#             */
/*   Updated: 2024/12/17 23:06:28 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize == 0 || dst_len >= dstsize)
		return (dstsize + src_len);
	i = dst_len;
	n = 0;
	while (src[n] != '\0' && (n < dstsize - dst_len - 1))
	{
		dst[i] = src[n];
		i++;
		n++;
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}
