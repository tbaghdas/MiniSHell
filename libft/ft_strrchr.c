/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:32:54 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/02/07 01:33:37 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	char	*loc;

	loc = ft_strchr(s, c);
	last = loc;
	while (loc && *loc)
	{
		last = loc;
		loc = ft_strchr(loc + 1, c);
	}
	return (last);
}
