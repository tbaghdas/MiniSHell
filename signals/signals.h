/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:42:36 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/10 13:30:22 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;
typedef struct s_shell	t_shell;

void	sigint_handler(int sig);
void	setup_signals(void);
void	handle_ctrl_d(t_shell *shell);
void	sig_monitoring(t_shell *shell);

#endif