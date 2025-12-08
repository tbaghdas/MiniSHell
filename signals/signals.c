/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:55:08 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/08 11:04:54 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	g_signum = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_ctrl_d(t_shell *shell)
{
	shell->exit_code = 0;
	write(1, "exit\n", 5);
	rl_clear_history();
	free_front_end_shell(shell);
	free_env(shell);
	exit(0);
}

void	sigquit_handler(int sig)
{
	g_signum = sig;
}

void	setup_signals(void)
{
	rl_clear_history();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	sig_monitoring(t_shell *shell)
{
	if (g_signum != 0)
	{
		shell->exit_code = 128 + g_signum;
		g_signum = 0;
	}
}
