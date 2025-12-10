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

void	ft_setenv(char *key, int *ex_ap_flags, char *value, t_shell *shell)
{
	t_env	*current;
	char	*tmp;

	current = shell->env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (current->value != NULL && ex_ap_flags[1] == 1)
			{
				tmp = ft_strjoin(current->value, value);
				free(current->value);
				current->value = tmp;
			}
			else
			{
				safe_free(current->value);
				current->value = ft_strdup(value);
			}
			current->export_flag = ex_ap_flags[0];
			return ;
		}
		current = current->next;
	}
	add_env(ex_ap_flags[0], key, value, shell);
}

void	add_env(int ex_flag, char *key, char *value, t_shell *shell)
{
	t_env	*new_node;

	if (key == NULL)
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
	new_node->export_flag = ex_flag;
	new_node->next = NULL;
	add_node_to_env_list(shell, new_node);
}

char	**get_env_array(t_env *env, int export_flag)
{
	char	**env_array;
	t_env	*current;
	int		i;

	if (env == NULL)
		return (NULL);
	env_array = malloc(sizeof(char *) * (list_size(env) + 1));
	if (env_array == NULL)
		return (NULL);
	current = env;
	i = 0;
	while (current != NULL)
	{
		if ((export_flag && current->export_flag) || export_flag == 0)
		{
			setting_line(&env_array[i], current);
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
