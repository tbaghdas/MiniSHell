/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:36:50 by ilya              #+#    #+#             */
/*   Updated: 2025/08/09 01:02:35 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	init_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("./pipex: fork");
		return (0);
	}
	return (1);
}

static void	exit_status(pid_t pid, int stat, t_chld *ctx)
{
	int	code;

	if (WIFEXITED(stat))
	{
		code = WEXITSTATUS(stat);
		if (pid == ctx->pid2)
			ctx->exit_code = code;
	}
}

static int	signal_status(int stat)
{
	int		sig;

	if (!WIFSIGNALED(stat))
		return (0);
	sig = WTERMSIG(stat);
	if (sig == SIGPIPE)
	{
		return (0);
	}
	return (EXIT_FAILURE);
}

static int	handle_children(t_chld *ctx)
{
	int		stat;
	pid_t	pid;

	ctx->exit_code = -1;
	pid = wait(&stat);
	while (pid > 0)
	{
		if (WIFEXITED(stat))
			exit_status(pid, stat, ctx);
		else
		{
			if (signal_status(stat))
				return (EXIT_FAILURE);
		}
		pid = wait(&stat);
	}
	return (ctx->exit_code);
}

int	exec(t_pipex *pipex, t_chld *ctx, char **envp)
{
	if (pipe(ctx->pipefd) == -1)
		return (perror("./pipex: pipe"), 0);
	if (!init_fork(&ctx->pid1))
		return (0);
	if (ctx->pid1 == 0)
		piper_cmd1(pipex, ctx, envp);
	if (!init_fork(&ctx->pid2))
		return (0);
	if (ctx->pid2 == 0)
		piper_cmd2(pipex, ctx, envp);
	close(ctx->pipefd[0]);
	close(ctx->pipefd[1]);
	return (handle_children(ctx));
}
