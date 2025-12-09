/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:06:37 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/09 20:07:06 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

// void	change_shlvl_value(t_env **env, char **cmd)
// {
// 	t_env	*tmp;
// 	int		res;

// 	tmp = *env;
// 	res = 0;
// 	if (ft_strcmp(cmd[0], "./minishell") == 0 && cmd[1] == NULL)
// 	{
// 		while (tmp)
// 		{
// 			if (ft_strcmp(tmp->key, "SHLVL") == 0)
// 			{
// 				if (tmp->value)
// 					res = ft_atoi(tmp->value);
// 				free(tmp->value);
// 				tmp->value = ft_itoa(res + 1);
// 				return ;
// 			}
// 			tmp = tmp->next;
// 		}
// 	}
// }