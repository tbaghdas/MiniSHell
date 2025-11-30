/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:54:20 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/11/30 16:39:32 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	built_in_env(t_env *env)
{
	if (env == NULL)
	{
		return (1);
	}
	if (print_env(get_env_array(env)) == -1)
	{
		return (1);
	}
	return (0);
}

int	built_in_exit(char *args)
{
	char	**splt;

	if (args == NULL || args[0] == '\0' || ft_isdigit(args) == -1)
	{
		write(2, "exit\nminishell: exit: ", 23);
		write(2, args, ft_strlen(args));
		write(2, ": numeric argument required\n", 29);
		// g_exit_status = 2;
		// free_all(env, stack, split);
		exit(2);
	}
	splt = ft_split(args, ' ');/////////////////the args are splited already the logic must move in wrapper 
	if (splt == NULL || splt[0] == NULL)
	{
		return (1);
	}
	if (splt[1] != NULL)
	{
		// g_exit_status = 127; // 1 not 127
		write(1, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
}
