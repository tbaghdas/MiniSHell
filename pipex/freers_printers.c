/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freers_printers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 01:01:15 by ikiriush          #+#    #+#             */
/*   Updated: 2025/08/09 01:29:47 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_error_printer(char *str)
{
	if (str && str[0] != ' ')
	{
		ft_putstr_fd("./pipex: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

void	arg_error_printer(void)
{
	ft_putstr_fd("Error: invalid number of arguments\n", 2);
	ft_putstr_fd("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 2);
}

void	freer(char ***arr)
{
	int	i;

	i = 0;
	if (arr == NULL || *arr == NULL)
		return ;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	str_freer(char **str)
{
	int	i;

	i = 0;
	if (str == NULL || *str == NULL)
		return ;
	free(*str);
	*str = NULL;
}

void	pipex_cleaner(t_pipex *pipex)
{
	if (pipex->cmd1)
		str_freer(&pipex->cmd1);
	if (pipex->cmd2)
		str_freer(&pipex->cmd2);
	if (pipex->cmd1_path)
		str_freer(&pipex->cmd1_path);
	if (pipex->cmd2_path)
		str_freer(&pipex->cmd2_path);
	if (pipex->cmd1_args)
		freer(&(pipex->cmd1_args));
	if (pipex->cmd2_args)
		freer(&(pipex->cmd2_args));
	fd_closer (pipex);
}
