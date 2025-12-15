/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:54:20 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/15 17:24:54 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_in_env(char **args, t_shell *shell)
{
	if (args != NULL && args[0] != NULL && args[1] != NULL)
	{
		write(2, "minishell: env: too many arguments\n", 35);
		return (shell->exit_code = 1, 1);
	}
	if (shell->env == NULL)
	{
		return (shell->exit_code = 1, 1);
	}
	if (print_env(get_env_array(shell->env, 1), 0) == -1)
	{
		return (shell->exit_code = 1, 1);
	}
	return (0);
}

int	built_in_exit(char **args, t_shell *shell)
{
	if (args == NULL || args[0] == NULL || args[1] == NULL
		|| args[1][0] == '\0' || isdigit_str(args[1]) == -1)
	{
		if (args[1] != NULL && isdigit_str(args[1]) == -1)
		{
			write(2, args[1], ft_strlen(args[1]));
			write (2, ": numeric argument required\n", 28);
			shell->exit_code = 2;
		}
		free_all(shell, NULL);
		exit(shell->exit_code);
	}
	if (args[1] != NULL && args[2] != NULL && args[2][0] != '\0')
	{
		shell->exit_code = 1;
		write(1, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	write(1, "exit\n", 5);
	shell->exit_code = (ft_atoi(args[1]) & 0xFF);
	free_all(shell, NULL);
	exit(shell->exit_code);
}
