/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:40:32 by ikiriush          #+#    #+#             */
/*   Updated: 2025/01/30 20:40:38 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	header(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j] != '\0' && s1[i] != '\0')
	{
		if ((s1[i] == set[j]) && (s1[i] != '\0') && (set[j] != '\0'))
		{
			i++;
			j = -1;
		}
		j++;
	}
	return (i);
}

static int	tailer(char const *s1, char const *set)
{
	size_t	i;
	int		j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (set[j] != '\0' && i > 0)
	{
		if ((s1[i] == set[j]))
		{
			i--;
			j = -1;
		}
		j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		head;
	int		tail;
	char	*ptr;
	int		i;

	if (set[0] == '\0' || s1[0] == '\0')
		return (ft_strdup(s1));
	head = header(s1, set);
	tail = tailer(s1, set);
	i = 0;
	if (header(s1, set) <= tailer(s1, set))
	{
		ptr = (char *)malloc((tail - head + 2) * sizeof(char));
		if (ptr == NULL)
			return (NULL);
		while (head <= tail)
			ptr[i++] = s1[head++];
	}
	else
		return (ft_strdup("\0"));
	ptr[i] = '\0';
	return (ptr);
}
