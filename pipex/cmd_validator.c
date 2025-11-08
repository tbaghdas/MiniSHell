/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:13:10 by ilya              #+#    #+#             */
/*   Updated: 2025/08/09 01:41:08 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		++i;
	}
	return (i);
}

int	is_direct_path(const char *arg)
{
	char	*first_word;
	int		result;

	if (!arg)
		return (0);
	first_word = ft_substr(arg, 0, ft_strcspn(arg, " \t"));
	if (!first_word)
		return (0);
	result = ((ft_strncmp(first_word, "./", 2) == 0
				|| ft_strncmp(first_word, "/", 1) == 0
				|| ft_strncmp(first_word, "../", 3) == 0));
	free(first_word);
	return (result != 0);
}

static char	*build_full_path(char *path, char *cmd)
{
	char	*full_path;
	size_t	len;

	if (!cmd)
		return (0);
	len = ft_strlen(path) + ft_strlen(cmd) + 2;
	full_path = malloc(len * sizeof(char));
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, path, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, cmd, len);
	return (full_path);
}

static char	*search_in_path(char *arg, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = build_full_path(paths[i], arg);
		if (!full_path)
		{
			i++;
			continue ;
		}
		if (access(full_path, X_OK) == 0)
			return (freer(&paths), full_path);
		free (full_path);
		i++;
	}
	freer(&paths);
	return (NULL);
}

char	*cmd_validator(char *arg, char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (search_in_path(arg, paths));
}
