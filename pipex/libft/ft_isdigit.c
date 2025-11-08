/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:43:34 by ikiriush          #+#    #+#             */
/*   Updated: 2025/01/21 11:43:38 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The c argument is an int, the value of which the application
   shall ensure is a character representable as an unsigned char or
   equal to the value of the macro EOF. If the argument has any
   other value, the behavior is undefined. */

#include "libft.h"

int	ft_isdigit(int c)
{
	unsigned char	cu;

	cu = (unsigned char)c;
	if (c < 0 || c > 255)
		return (0);
	if (c == EOF)
		return (0);
	if (cu >= '0' && cu <= '9')
		return (1);
	else
		return (0);
}
