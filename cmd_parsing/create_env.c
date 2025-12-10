/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:59:07 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/11 00:32:37 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// //env level by calling the minishell, bash, zsh...etc

int	init_env(t_shell *shell, char **envp)
{
	int		i;
	char	*equal_sign;
	t_env	*new_node;

	if (envp == NULL)
		return (1);
	i = -1;
	while (envp[++i] != NULL)
	{
		equal_sign = ft_strchr(envp[i], '=');
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (free_env(shell), 1);
		init_node_fields(new_node, envp[i], equal_sign);
		add_node_to_env_list(shell, new_node);
	}
	return (0);
}

void	init_node_fields(t_env *node, char *env_str, char *equal_sign)
{
	size_t	key_len;

	if (equal_sign)
	{
		key_len = equal_sign - env_str;
		node->key = ft_substr(env_str, 0, key_len);
		node->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		node->key = ft_strdup(env_str);
		node->value = NULL;
	}
	node->export_flag = true;
	node->next = NULL;
}

void	add_node_to_env_list(t_shell *shell, t_env *new_node)
{
	t_env	*temp;

	if (shell->env == NULL)
	{
		shell->env = new_node;
	}
	else
	{
		temp = shell->env;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	free_env(t_shell *shell)
{
	t_env	*current;
	t_env	*next;

	current = shell->env;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	shell->env = NULL;
}
