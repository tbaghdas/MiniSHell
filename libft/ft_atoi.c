/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:06:59 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/07/10 18:44:07 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *s)
{
	long	res;
	long	i;
	long	sign;

	res = 0;
	i = 0;
	sign = 1;
	if (s[i] < 0)
		return (res);
	while (s[i] && (s[i] == 32 || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (s[i] == 45 || s[i] == 43)
	{
		if (s[i] == 45)
			sign *= -1;
		i++;
	}
	while (s[i] > 47 && s[i] < 58)
		res = res * 10 + s[i++] - '0';
	return (res * sign);
}
/*
int	ft_atoi(const char *s)
{
	int	res;
	int	i;
	int	sign;

	res = 0;
	i = 0;
	sign = 1;
	if (!s)
		return (res);
	while (s[i] && (s[i] < 33 || s[i] == 43 || s[i] == 45))
	{
		if (s[i] == 45)
			sign *= -1;
		i++;
	}
	while (s[i] > 47 && s[i] < 58)
		res = res * 10 + s[i++] - '0';
	return (res * sign);
}
*/