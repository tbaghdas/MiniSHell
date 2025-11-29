/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:55:08 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/11/29 18:55:11 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_ctrl_d(void)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	// g_exit_status = 0;
	// exit(g_exit_status);
	exit(0);
}

void	sigquit_handler(int sig)
{
	sig++;
}

void	setup_signals(void)
{
	rl_clear_history();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
