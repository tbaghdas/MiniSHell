/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 01:11:26 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/11 01:21:54 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_external_or_builtin_in_parent(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;
	char	**envp;
	int		code;

	if (cmd->redirs && apply_redirs(cmd) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->redirs->target, 2);
		write(2, ": ", 2), perror(""); //free_all(shell, NULL);
	}
	if (is_builtin(cmd->argv[0]))
	{
		code = execute_builtin(cmd, shell);
		// free_all(shell, NULL);
	}
	cmd_path = find_command_in_path(cmd->argv[0], shell->env);
	if (cmd_path == NULL)
	{
		print_cmd_not_found(cmd->argv[0]);
		// exit((free_all(shell, NULL), 127));
	}
	envp = get_env_array(shell->env, 1);
	execve(cmd_path, cmd->argv, envp);
	print_execve_err(cmd_path);
	free(cmd_path);//, free_all(shell, envp), 126));
}
