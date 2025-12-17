/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:02:03 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/17 15:44:42 by tbaghdas         ###   ########.fr       */
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->redirs->target, 2);
		exit((write(2, ": ", 2), perror(""), free_all(shell, NULL), 1));
	}
	if (is_builtin(cmd->argv[0]))
	{
		code = execute_builtin(cmd, shell);
		exit((free_all(shell, NULL), code & 0xFF));
	}
	cmd_path = find_command_in_path(cmd->argv[0], shell->env);
	if (cmd_path == NULL)
	{
		print_cmd_not_found(cmd->argv[0]);
		exit((free_all(shell, NULL), 127));
	}
	envp = get_env_array(shell->env, 1);
	if (cmd_path[0] != '\0')
		ex_err((my_execve(cmd_path, cmd->argv, envp, shell), cmd_path), shell);
	exit((free(cmd_path), free_all(shell, envp), 0));
}

void	child_process(int pipefd[2], int *prev_fd, t_cmd *cur, t_shell *shell)
{
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (cur->next)
		dup2(pipefd[1], STDOUT_FILENO);
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	run_external_or_builtin_in_child(cur, shell);
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
	else
	{
		if (pipefd[0] != -1)
			close(pipefd[0]);
		if (pipefd[1] != -1)
			close(pipefd[1]);
	}
}

int	this_while_body(int *prev_fd, t_cmd *cur, t_shell *shell, pid_t *last)
{
	int		pipefd[2];
	pid_t	pid;

	pipefd[0] = -1;
	pipefd[1] = -1;
	if (cur->next)
	{
		if (pipe(pipefd) == -1)
			return (perror("minishell: pipe"), shell->exit_code = 1, 1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), shell->exit_code = 1, 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process(pipefd, prev_fd, cur, shell);
	}
	if (cur->next == NULL && last)
		*last = pid;
	return (closing_fds(pipefd, prev_fd, cur->next), 0);
}

int	execute_pipeline(t_cmd *start, t_shell *shell)
{
	t_cmd	*cur;
	int		prev_fd;
	pid_t	last;

	prev_fd = -1;
	last = -1;
	cur = start;
	while (cur)
	{
		if (this_while_body(&prev_fd, cur, shell, &last) != 0)
			return (1);
		cur = cur->next;
	}
	signal_waiter(last, shell);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	return (shell->exit_code);
}
