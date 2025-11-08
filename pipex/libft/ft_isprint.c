/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:06:43 by ikiriush          #+#    #+#             */
/*   Updated: 2025/01/23 13:06:46 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isprint(int c)
{
	unsigned char	cu;

	cu = (unsigned char)c;
	if (c < 0 || c > 255)
		return (0);
	if (c == EOF)
		return (0);
	if (cu >= 32 && cu <= 126)
		return (1);
	else
		return (0);
}
