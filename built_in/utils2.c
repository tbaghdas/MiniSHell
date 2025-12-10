/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:54:53 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/11 01:05:18 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(char **env, int export)
{
	int		i;

	if (env == NULL)
	{
		return (-1);
	}
	i = 0;
	while (env[i] != NULL)
	{
		if (export == 1)
			print_export_style(env[i]);
		else
			ft_putstr_fd(env[i], 1);
		write(1, "\n", 1);
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

int	check_for_export(char **str, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*equal_sign;
	char	*delim;

	while (*str)
	{
		if (check_export_arg(*str) != 0)
			return (-1);
		equal_sign = ft_strchr(*str, '=');
		delim = get_delim(*str, equal_sign);
		if (equal_sign != NULL)
		{
			key = ft_substr(*str, 0, delim - *str);
			value = ft_strdup(equal_sign + 1);
		}
		else
			key = ft_strdup((value = ft_strdup(ft_getenv(*str, shell->env)),
						*str));
		ft_setenv(key, check_append(1, *str), value, shell);
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
		if (!ft_isalnum(str[i]) && str[i] != '_'
			&& !(str[i] == '+' && str[i + 1] == '='))
		{
			print_export_err(str);
			return (-1);
		}
		i++;
	}
	return (0);
}
