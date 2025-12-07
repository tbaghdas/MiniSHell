/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:02:03 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/07 18:42:19 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_external_or_builtin_in_child(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;
	char	**envp;
	int		code;

	if (cmd->redirs && apply_redirs(cmd) == -1)
	{
		ft_putstr_fd("minishell: redirection failed\n", 2);
		exit(1);
	}
	if (is_builtin(cmd->argv[0]))
	{
		code = execute_builtin(cmd, shell);
		exit(code & 0xFF);
	}
	cmd_path = find_command_in_path(cmd->argv[0], shell->env);
	if (cmd_path == NULL)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->argv[0], 2);
		exit(127);
	}
	envp = get_env_array(shell->env);
	execve(cmd_path, cmd->argv, envp);
	perror("minishell: execve");
	free(cmd_path); /// free envp
	exit(126);
}

void	the_child_process(int pipefd[2], int prev_fd, t_cmd *cur, t_shell *shell)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cur->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	/* run command in child (externals or builtins) */
	run_external_or_builtin_in_child(cur, shell);
	/* never reached */
}

void	closing_fds(int pipefd[2], int *prev_fd, t_cmd *has_next)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (has_next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

void	this_while_body(int *prev_fd, t_cmd *cur, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;

	if (cur->next)
	{
		if (pipe(pipefd) == -1)
			return (perror("minishell: pipe"), 1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		the_child_process(pipefd, prev_fd, cur, shell);
	closing_fds(pipefd, &prev_fd, cur->next);
}

int	execute_pipeline(t_cmd *start, t_shell *shell)
{
	t_cmd	*cur;
	int		prev_fd;
	int		status;
	int		last_status;

	prev_fd = -1;
	cur = start;
	last_status = 0;
	while (cur)
	{
		this_while_body(&prev_fd, cur, shell);
		cur = cur->next;
	}
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	}
	return (last_status);
}
