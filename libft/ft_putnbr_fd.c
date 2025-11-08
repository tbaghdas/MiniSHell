/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:44:49 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/02/13 21:28:40 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	long	div;

	nb = n;
	div = 10;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	while (nb / (div * 10))
	{
		div *= 10;
	}
	while (div > 2 && nb > 9)
	{
		ft_putchar_fd((nb / div) % 10 + '0', fd);
		div /= 10;
	}
	ft_putchar_fd((nb % 10) + '0', fd);
}
