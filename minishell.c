/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:58:54 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/10 21:27:57 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(t_shell *sh)
{
	char	*line;

	while (42)
	{
		sig_monitoring(sh);
		line = readline("minishell$ ");
		if (!line)
		{
			handle_ctrl_d(sh);
			break ;
		}
		if (*line)
			add_history(line);
		if (parse_input(sh, line) != 0)
		{
			free_front_end_shell(sh);
			continue ;
		}
		process_heredoc(sh);
		// print_cmds(sh);
		cmd_parser(sh);
		free(line);
		free_front_end_shell(sh);
	}
}
