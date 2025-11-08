/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:22:30 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/02/01 17:57:45 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	length;
	char			*str;

	if (!s || !f)
		return (NULL);
	length = ft_strlen(s);
	str = (char *) malloc(++length * sizeof(char));
	if (!str)
		return (NULL);
	length = -1;
	while (s[++length])
		str[length] = f(length, s[length]);
	str[length] = '\0';
	return (str);
}
