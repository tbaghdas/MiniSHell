/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:47:12 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/02/13 21:21:45 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_str(char *str, long nb, int count)
{
	str[count--] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb / 10)
	{
		str[count--] = nb % 10 + '0';
		nb /= 10;
	}
	str[count] = nb + '0';
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;
	long	nb;

	count = 2;
	if (n < 0)
		count++;
	nb = n;
	while (n / 10)
	{
		++count;
		n /= 10;
	}
	str = (char *) malloc(count-- * sizeof(char));
	if (!str)
		return (NULL);
	write_str(str, nb, count);
	return (str);
}
