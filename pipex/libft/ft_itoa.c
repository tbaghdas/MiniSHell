/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:23:54 by ikiriush          #+#    #+#             */
/*   Updated: 2025/07/01 01:20:19 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*cornercases(int nb, char *buf)
{
	if (nb == 0)
		ft_strlcpy (buf, "0", 2);
	if (nb == 1)
		ft_strlcpy (buf, "1", 2);
	if (nb > 1 && nb <= 9)
	{
		buf[0] = nb + '0';
		buf[1] = '\0';
	}
	if (nb <= -1 && nb >= -9)
	{
		buf[0] = '-';
		buf[1] = -nb + '0';
		buf[2] = '\0';
	}
	if (nb == -2147483648)
		ft_strlcpy (buf, "-2147483648", 12);
	return (buf);
}

static char	*print(int nb, int m, char *buf)
{
	char	d;
	int		i;

	buf[0] = '0';
	d = nb / 10000000000 + '0';
	while (d == '0')
	{
		d = nb / (1000000000 / m) + '0';
		m = m * 10;
		if (d != '0')
			buf[1] = d;
	}
	i = 2;
	while (m < 214748364)
	{
		d = nb / (1000000000 / m) % 10 + '0';
		m = m * 10;
		buf[i++] = d;
	}
	d = nb % 10 + '0';
	if (nb > 9)
		buf[i] = d;
	buf [i + 1] = '\0';
	return (buf);
}

char	*ft_itoa(int n)
{
	char	buf[12];
	char	*buff;
	char	*ptr;
	int		neg;

	neg = 0;
	if (n == 0 || (n > 0 && n <= 9) || (n <= -1 && n >= -9) || n == -2147483648)
	{
		buff = cornercases(n, buf);
		return (ptr = ft_strdup(buf));
	}
	if (n < 0)
	{
		n = n * (-1);
		neg = 1;
	}
	buff = print(n, 1, buf);
	if (neg == 1)
	{
		buf[0] = '-';
		ptr = ft_strdup(buff);
	}
	else
		ptr = ft_strdup(buff + 1);
	return (ptr);
}
