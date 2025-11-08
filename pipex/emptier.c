/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emptier.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 01:03:41 by ikiriush          #+#    #+#             */
/*   Updated: 2025/08/09 01:30:17 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	empty_handler1(char **argv)
{
	int	len;

	if (!argv[2] || argv[2][0] == '\0')
	{
		ft_putstr_fd("./pipex: command not found\n", 2);
		return (1);
	}
	else
	{
		len = ft_strlen(argv[2]);
		if (argv[2] && (argv[2][0] == '\0' || argv[2][0] == ' '
			|| (len > 0 && argv[2][len - 1] == ' ')))
		{
			cmd_error_printer(argv[2]);
			return (1);
		}
	}
	return (0);
}

static int	empty_handler2(char **argv)
{
	int	len;

	if (!argv[3] || argv[3][0] == '\0')
	{
		ft_putstr_fd("./pipex: command not found\n", 2);
		return (1);
	}
	else
	{
		len = ft_strlen(argv[3]);
		if (argv[3] && (argv[3][0] == '\0' || argv[3][0] == ' '
			|| (len > 0 && argv[3][len - 1] == ' ')))
		{
			cmd_error_printer(argv[3]);
			return (1);
		}
	}
	return (0);
}

void	empty_handler(char **argv, t_pipex *pipex)
{
	int	fd;

	if (empty_handler1(argv))
		pipex->empty1 = 1;
	if (empty_handler2(argv))
	{
		fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd >= 0)
			close (fd);
		exit(127);
	}
}
