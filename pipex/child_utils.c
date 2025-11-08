/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 00:34:47 by ikiriush          #+#    #+#             */
/*   Updated: 2025/08/09 01:29:57 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_basename(char *path)
{
	char	*slash;

	if (ft_strncmp(path, "./", 2) == 0)
		return (strchr(path, '.'));
	slash = strrchr(path, '/');
	if (slash)
		return (slash + 1);
	return (path);
}

void	exec_checker(char *path, t_pipex *pipex, t_chld *ctx, int no)
{
	char	*cmd;

	if (path && access(path, F_OK) == 0 && access(path, X_OK) == -1)
	{
		cmd = get_basename(path);
		ft_putstr_fd("./pipex: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		close_io_fds(pipex);
		if (no == 1)
			close (ctx->pipefd[1]);
		if (no == 2)
			close (ctx->pipefd[0]);
		pipex_cleaner(pipex);
		exit(126);
	}
}
