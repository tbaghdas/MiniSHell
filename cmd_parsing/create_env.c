/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:59:07 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/07 18:15:16 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// //env level by calling the minishell, bash, zsh...etc
////// envp in maiiin is char ******

int create_env(t_shell *shell, char **envp)
{
	int		i;
	char	*equal_sign;
	t_env	*new_node;

	shell->env = NULL;
	if (envp == NULL)
		return (1);
	i = 0;
	while (envp[i] != NULL)
	{
		equal_sign = ft_strchr(envp[i], '=');
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (1); // Memory allocation failed

		if (equal_sign)
		{
			size_t key_len = equal_sign - envp[i];
			new_node->key = ft_substr(envp[i], 0, key_len);
			new_node->value = ft_strdup(equal_sign + 1);
		}
		else
		{
			new_node->key = ft_strdup(envp[i]);
			new_node->value = NULL;
		}
		new_node->export_flag = true; // By default, all env vars are exported
		new_node->next = NULL;

		if (shell->env == NULL)
		{
			shell->env = new_node;
		}
		else
		{
			t_env *temp = shell->env;
			while (temp->next)
				temp = temp->next;
			temp->next = new_node;
		}
		i++;
	}
	return (0); // Success
}
