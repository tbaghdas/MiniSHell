/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:14:00 by ikiriush          #+#    #+#             */
/*   Updated: 2025/01/26 22:14:09 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	unsigned char	cu;

	cu = (unsigned char)c;
	if (c == EOF)
		return (c);
	if (cu >= 'A' && cu <= 'Z')
		return (cu + 32);
	return (c);
}
