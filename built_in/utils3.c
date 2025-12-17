/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:26:41 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/17 15:43:26 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export_err(char *str)
{
	write(2, "minishell: export: `", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
}

void	free_export_key_value(char *key, char *value)
{
	if (key != NULL)
		free(key);
	if (value != NULL)
		free(value);
}

int	isdigit_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

void	free_all(t_shell *shell, char **env)
{
	free_fe_shell(shell);
	free_env(shell);
	if (env != NULL)
		free_split(env);
}

int	list_size(t_env *env)
{
	t_env	*current;
	int		size;

	current = env;
	size = 0;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}
