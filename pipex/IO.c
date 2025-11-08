/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 00:15:48 by ikiriush          #+#    #+#             */
/*   Updated: 2025/08/09 01:28:23 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fd_closer(t_pipex *pipex)
{
	if (pipex->in_fd >= 0)
		close(pipex->in_fd);
	if (pipex->out_fd >= 0)
		close(pipex->out_fd);
}

static int	infile_validator(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("./pipex: ", 2);
		ft_putstr_fd(infile, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		fd = open("/dev/null", O_RDONLY);
		if (fd == -1)
		{
			perror("/.pipex: /dev/null");
			return (-1);
		}
	}
	return (fd);
}

static int	outfile_validator(char *outfile, t_pipex *pipex)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("./pipex: ", 2);
		ft_putstr_fd(outfile, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		pipex_cleaner(pipex);
		exit(1);
	}
	return (fd);
}

int	init_fds(char **argv, t_pipex *pipex)
{
	pipex->in_fd = infile_validator(argv[1]);
	pipex->out_fd = outfile_validator(argv[4], pipex);
	return (pipex->in_fd >= 0 && pipex->out_fd >= 0);
}
