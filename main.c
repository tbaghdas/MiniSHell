/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:48:28 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/08 14:29:08 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signum;

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	sh = (t_shell){0};
	if (init_env(&sh, envp) != 0)
		return (1);
	//init_shell(&sh, envp);
	main_loop(&sh, envp);
	free_front_end_shell(&sh);
	free_env(&sh);
	return (sh.exit_code);
}
