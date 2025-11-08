/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:16:22 by ikiriush          #+#    #+#             */
/*   Updated: 2025/01/21 12:16:24 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The c argument is an int, the value of which the application
   shall ensure is representable as an unsigned char or equal to the
   value of the macro EOF. If the argument has any other value, the
   behavior is undefined. */

#include "libft.h"

int	ft_isalnum(int c)
{
	unsigned char	cu;

	cu = (unsigned char)c;
	if (c == EOF)
		return (0);
	if (((cu >= 'A' && cu <= 'Z') || (cu >= 'a' && cu <= 'z'))
		|| (cu >= '0' && cu <= '9'))
		return (1);
	else
		return (0);
}
