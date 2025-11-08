/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:35:16 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/02/13 21:36:10 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	rem_count_start(char const *s1, char const *set)
{
	int		count;
	int		i;
	int		j;
	char	flag;

	flag = 1;
	j = 0;
	i = 0;
	count = -1;
	while (s1[i] && flag)
	{
		flag = 0;
		count++;
		j = 0;
		while (set[j] && !flag)
		{
			if (s1[i] == set[j++])
				flag = 1;
		}
		i++;
	}
	return (count);
}

static int	rem_count_end(char const *s1, char const *set, int i)
{
	int		count;
	int		j;
	char	flag;

	flag = 1;
	j = 0;
	count = -1;
	while (i >= 0 && flag)
	{
		flag = 0;
		count++;
		j = 0;
		while (set[j] && !flag)
		{
			if (s1[i] == set[j++])
				flag = 1;
		}
		i--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		len;
	int		start_count;
	int		end_count;
	int		i;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen((char *)s1);
	start_count = rem_count_start(s1, set);
	end_count = rem_count_end(s1, set, len - 1);
	if (start_count + end_count >= len || !s1[0])
		return (ft_strdup(""));
	str = (char *) malloc((len - start_count - end_count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (start_count < len - end_count)
		str[i++] = s1[start_count++];
	str[i] = '\0';
	return (str);
}
