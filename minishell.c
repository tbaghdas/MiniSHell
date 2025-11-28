/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:58:54 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/29 03:56:00 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(t_shell *sh, char **envp)
{
	char	*line;

	while (1)
		{
			line = readline("minishell$ ");
			if (!line)
			{
				ft_putstr_fd("exit\n", STDOUT_FILENO);
				break;
			}
			if (*line)
				add_history(line);
			if (parse_input(&sh, envp, line) == 0)
//				execute_commands(&sh);
			free(line);
			// cleanup_after_command(&sh);
		}
}