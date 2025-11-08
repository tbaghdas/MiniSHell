/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:20:23 by ikiriush          #+#    #+#             */
/*   Updated: 2025/06/29 22:46:18 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter(char const *s, char c)
{
	int	i;
	int	n;
	int	ctr;

	ctr = 0;
	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == c)
			n = 0;
		else if (n == 0)
		{
			n = 1;
			ctr++;
		}
		i++;
	}
	return (ctr);
}

static char	*allocator(char const *s, char c)
{
	char	*ptr;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	ptr = (char *)malloc(sizeof(char) * i + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static char	**freer(char **s, int i)
{
	while (--i >= 0)
		if (s[i])
			free(s[i]);
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	ptr = (char **)malloc(sizeof(char *) * (counter(s, c) + 1));
	if (!ptr)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			ptr[i++] = allocator(s, c);
			if (ptr[i - 1] == NULL)
				return (freer(ptr, i));
			while (*s && *s != c)
				s++;
		}
	}
	ptr[i] = NULL;
	return (ptr);
}
