/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 01:40:56 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/16 02:31:48 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_waiter(t_shell *sh)
{
	int		status;
	int		last_status;

	last_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
		sh->exit_code = last_status;
	}
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
	exit(130);
}

int	wait_heredoc_child(pid_t pid, t_shell *sh)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	if (WIFEXITED(status))
		sh->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->exit_code = 128 + WTERMSIG(status);
	return (0);
}
