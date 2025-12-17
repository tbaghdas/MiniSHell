/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 01:11:26 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/17 15:45:09 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_execve(char *path, char **argv, char **envp, t_shell *shell)
{
	struct stat	st;
	int			exit_code;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			exit((free(path), free_all(shell, envp), 126));
		}
	}
	if (execve(path, argv, envp) == -1)
	{
		exit_code = 126;
		if (errno == ENOENT || errno == ENOTDIR)
			exit_code = 127;
		perror(path);
		exit((free(path), free_all(shell, envp), exit_code));
	}
	exit((free(path), free_all(shell, envp), 1));
}

int	execute_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int	original_stdout;
	int	original_stdin;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	if (original_stdout == -1 || original_stdin == -1)
	{
		perror("dup");
		return (shell->exit_code = 1, 1);
	}
	if (apply_redirs(cmd) < 0)
		return (shell->exit_code = 1, perror(" "), 1);
	execute_builtin(cmd, shell);
	if (dup2(original_stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2 stdout restore");
	}
	close(original_stdout);
	if (dup2(original_stdin, STDIN_FILENO) == -1)
	{
		perror("dup2 stdin restore");
	}
	close(original_stdin);
	return (shell->exit_code);
}
