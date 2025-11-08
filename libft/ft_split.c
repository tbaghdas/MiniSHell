/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:23:11 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/02/13 21:29:22 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_count(char const *s, char c)
{
	char	flag;
	int		count;
	int		i;

	i = 0;
	count = 0;
	flag = 1;
	while (s[i])
	{
		if (s[i] != c && flag)
		{
			count++;
			flag = 0;
		}
		else if (s[i] == c)
			flag = 1;
		i++;
	}
	return (count);
}

static int	get_size(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] && s[i++] != c)
		++count;
	return (count);
}

static int	free_mem(char **strs, int i)
{
	while (i >= 0)
		free(strs[i--]);
	free(strs);
	return (1);
}

static int	gen_strs(char **strs, char const *s, char c, int *arr)
{
	int		i;

	i = 0;
	while (s[i] && arr[1] < arr[0])
	{
		if (s[i] == c || arr[1] == -1)
		{
			while (s[i] == c)
				++i;
			arr[2] = 0;
			if (arr[1] + 1 == arr[0])
				break ;
			strs[++arr[1]] = (char *)malloc(
					(get_size(s + i, c) + 1) * sizeof(char));
			if (!strs[arr[1]])
				return (free_mem(strs, arr[1]));
		}
		strs[arr[1]][arr[2]++] = s[i++];
		if (arr[1] != -1 && (s[i] == c || !s[i]))
			strs[arr[1]][arr[2]] = '\0';
	}
	strs[arr[0]] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		count;
	int		arr[3];

	arr[1] = -1;
	arr[2] = 0;
	if (!s)
		return (NULL);
	count = words_count(s, c);
	if (count == 0)
	{
		strs = (char **) malloc(sizeof(char *));
		if (!strs)
			return (NULL);
		strs[0] = NULL;
		return (strs);
	}
	strs = (char **) malloc((count + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	arr[0] = count;
	if (gen_strs(strs, s, c, arr))
		strs = NULL;
	return (strs);
}
