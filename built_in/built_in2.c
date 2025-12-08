/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:54:20 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/08 13:00:34 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_in_env(char **args, t_shell *shell)
{
	if (args != NULL && args[0] != NULL)
	{
		write(2, "minishell: env: too many arguments\n", 35);
		return (shell->exit_code = 1, 1);
	}
	if (shell->env == NULL)
	{
		return (shell->exit_code = 1, 1);
	}
	if (print_env(get_env_array(shell->env, 0)) == -1)
	{
		return (shell->exit_code = 1, 1);
	}
	return (0);
}

int	built_in_exit(char **args, t_shell *shell)
{
	long	flag;

	if (args == NULL || args[0] == NULL
		|| args[0][0] == '\0' || isdigit_str(args[0][0]) == -1)
	{
		write(2, "exit\nminishell: exit: ", 23);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": numeric argument required\n", 29);
		shell->exit_code = 2;
		free_all(shell, NULL);
		exit(2);
	}
	if (args[1] != NULL)
	{
		shell->exit_code = 1;
		write(1, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	flag = ft_atoi(args[0]);
	write(1, "exit\n", 5);
	shell->exit_code = flag & 0xFF;
	free_all(shell, NULL);
	exit(flag & 0xFF);
}
