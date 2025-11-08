/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:38:50 by ikiriush          #+#    #+#             */
/*   Updated: 2025/01/21 11:39:08 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The standards require that the argument c for these functions is
   either EOF or a value that is representable in the type unsigned
   char; otherwise, the behavior is undefined.  If the argument c is
   of type char, it must be cast to unsigned char */

#include "libft.h"

int	ft_isalpha(int c)
{
	unsigned char	cu;

	cu = (unsigned char)c;
	if (c < 0 || c > 255)
		return (0);
	if (c == EOF)
		return (0);
	if ((cu >= 'A' && cu <= 'Z') || (cu >= 'a' && cu <= 'z'))
		return (1);
	else
		return (0);
}
