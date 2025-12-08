/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:54:29 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/11/29 18:54:29 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *key, t_env *env)
{
	t_env	*current;

	if (key == NULL || env == NULL)
	{
		return (NULL);
	}
	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

void	ft_setenv(char *key, t_env *env, char *value, t_shell *shell)
{
	t_env	*current;

	if (key == NULL || env == NULL || value == NULL)
	{
		return ;
	}
	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	add_env(&env, key, value, shell);
}

void	add_env(t_env **env, char *key, char *value, t_shell *shell)
{
	t_env	*new_node;

	if (key == NULL || value == NULL)
	{
		return ;
	}
	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		return ;
	}
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	add_node_to_env_list(shell, new_node);
	*env = new_node;
}

char	**get_env_array(t_env *env, int export_flag)
{
	char	**env_array;
	char	*temp;
	t_env	*current;
	int		i;

	if (env == NULL)
		return (NULL);
	env_array = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (env_array == NULL)
		return (NULL);
	current = env;
	i = 0;
	while (current != NULL)
	{
		if (!(export_flag && !current->export_flag))
		{
			env_array[i] = ft_strjoin(current->key, "=");
			temp = ft_strjoin(env_array[i], current->value);
			free(env_array[i]);
			env_array[i] = temp;
			i++;
		}
		current = current->next;
	}
	return (env_array[i] = NULL, env_array);
}

int	del_env(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (env == NULL || *env == NULL || key == NULL)
		return (-2);
	current = *env;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*env = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (-2);
}
