/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:28:54 by ikiriush          #+#    #+#             */
/*   Updated: 2025/01/24 12:28:57 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	unsigned char	cu;

	cu = (unsigned char)c;
	if (c == EOF)
		return (c);
	if (cu >= 'a' && cu <= 'z')
		return (cu - 32);
	return (c);
}
