/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 01:40:56 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/17 16:22:57 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_waiter(pid_t last, t_shell *sh)
{
	int		status;
	int		last_status;
	pid_t	pid;

	last_status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
	sh->exit_code = last_status;
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_signum = SIGINT;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

int	wait_heredoc_child(pid_t pid, t_shell *sh)
{
	int	status;
	int	code;

	code = 0;
	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	if (WIFEXITED(status))
		sh->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->exit_code = 128 + WTERMSIG(status);
	return (0);
}
