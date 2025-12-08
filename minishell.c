/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:58:54 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/08 15:11:52 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(t_shell *sh, char **envp)
{
	char	*line;

	while (42)
	{
		sig_monitoring(sh);
		line = readline("minishell$ ");
		if (!line)
		{
			handle_ctrl_d(sh);
			// ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (*line)
			add_history(line);
		if (parse_input(sh, envp, line) != 0)
		{
			free_front_end_shell(sh);
			continue ;
		}
		process_heredoc(sh);
		//print_cmds(sh);
		cmd_parser(sh);
		free(line);
		free_front_end_shell(sh);
	}
}
