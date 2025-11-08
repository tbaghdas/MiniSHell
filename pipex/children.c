/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 00:20:32 by ikiriush          #+#    #+#             */
/*   Updated: 2025/08/09 01:29:35 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_io_fds(t_pipex *pipex)
{
	if (pipex->in_fd >= 0)
		close(pipex->in_fd);
	if (pipex->out_fd >= 0)
		close(pipex->out_fd);
}

static void	prepare_input_fd(t_pipex *pipex, int *fd)
{
	close(fd[0]);
	dup2(pipex->in_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	piper_cmd1(t_pipex *pipex, t_chld *ctx, char **envp)
{
	if (pipex->empty1)
	{
		close(ctx->pipefd[0]);
		close_io_fds(pipex);
		pipex_cleaner(pipex);
		close(ctx->pipefd[1]);
		exit(127);
	}
	close(ctx->pipefd[0]);
	exec_checker(pipex->cmd1_path, pipex, ctx, 1);
	prepare_input_fd(pipex, ctx->pipefd);
	close_io_fds(pipex);
	if (execve(pipex->cmd1_path, pipex->cmd1_args, envp) == -1)
	{
		close(ctx->pipefd[1]);
		cmd_error_printer(pipex->cmd1);
		pipex_cleaner(pipex);
		exit(127);
	}
}

static void	prepare_output_fd(t_pipex *pipex, t_chld *ctx)
{
	close(ctx->pipefd[1]);
	dup2(ctx->pipefd[0], STDIN_FILENO);
	dup2(pipex->out_fd, STDOUT_FILENO);
	close(ctx->pipefd[0]);
}

void	piper_cmd2(t_pipex *pipex, t_chld *ctx, char **envp)
{
	close(ctx->pipefd[1]);
	exec_checker(pipex->cmd2_path, pipex, ctx, 2);
	prepare_output_fd(pipex, ctx);
	close_io_fds(pipex);
	if (execve(pipex->cmd2_path, pipex->cmd2_args, envp) == -1)
	{
		close (ctx->pipefd[0]);
		cmd_error_printer(pipex->cmd2);
		pipex_cleaner(pipex);
		exit(127);
	}
}
