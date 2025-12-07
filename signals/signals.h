/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:42:36 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/07 19:22:58 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	sigint_handler(int sig);
void	setup_signals(void);
void	handle_ctrl_d(t_shell *shell);
void	sigquit_handler(int sig);
void	sig_monitoring(t_shell *shell);

#endif