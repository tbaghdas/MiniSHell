/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:54:53 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/08 14:02:46 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	free_split(env);
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

char	**sort_env(t_env *env, int export_flag)
{
	char	**env_array;
	char	*temp;
	int		i;
	int		j;

	env_array = get_env_array(env, export_flag);
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

int	check_for_export(char **str, t_env *env, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*equal_sign;
	t_env	*current;

	while (*str)
	{
		if (check_export_arg(*str) != 0)
			return (-1);
		equal_sign = ft_strchr(*str, '=');
		if (equal_sign != NULL)
		{
			key = ft_substr(*str, 0, equal_sign - *str);
			value = ft_strdup(equal_sign + 1);
		}
		else
		{
			key = ft_strdup(*str);
			value = NULL;
		}
		ft_setenv(key, env, value, shell);
		free_export_key_value(key, value);
		str++;
	}
	return (0);
}

int	check_export_arg(char *str)
{
	int	i;

	if (str[0] == '\0')
	{
		print_export_err("'");
		return (-1);
	}
	if (ft_isdigit(str[0]))
	{
		print_export_err(str);
		return (-1);
	}
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			print_export_err(str);
			return (-1);
		}
		i++;
	}
	return (0);
}
