/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:54:53 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/11/30 16:24:00 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	print_env(char **env)
{
	int	i;

	if (env == NULL)
	{
		return (-1);
	}
	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (1);
}

int	array_size(char **arr)
{
	int	size;

	if (arr == NULL)
		return (0);
	size = 0;
	while (arr[size] != NULL)
		size++;
	return (size);
}

char	**sort_env(t_env *env)
{
	char	**env_array;
	char	*temp;
	int		i;
	int		j;

	env_array = get_env_array(env);
	if (env_array == NULL)
		return (NULL);
	i = 0;
	while (i < array_size(env_array) - 1)
	{
		j = i + 1;
		while (j < array_size(env_array))
		{
			if (ft_strcmp(env_array[i], env_array[j]) > 0)
			{
				temp = env_array[i];
				env_array[i] = env_array[j];
				env_array[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (env_array);
}

int	check_for_export(char *str, t_env *env)
{
	char	*key;
	char	*value;
	char	*equal_sign;
	t_env	*current;

	if (check_export_arg(str) != 0)
		return (-1);
	equal_sign = ft_strchr(str, '=');
	if (equal_sign != NULL)
	{
		key = ft_substr(str, 0, equal_sign - str);
		value = ft_strdup(equal_sign + 1);
	}
	else
	{
		key = ft_strdup(str);
		value = NULL;
	}
	ft_setenv(key, env, value);
	free(key);
	if (value != NULL)
		free(value);
	return (0);
}

int	check_export_arg(char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (-1);
	if (ft_isdigit(str[0]))
	{
		write(2, "minishell: export: ", 19);
		write(2, str, ft_strlen(str));
		write(2, ": not a valid identifier\n", 25);
		return (-1);
	}
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			write(2, "minishell: export: ", 19);
			write(2, str, ft_strlen(str));
			write(2, ": not a valid identifier\n", 25);
			return (-1);
		}
		i++;
	}
	return (0);
}
