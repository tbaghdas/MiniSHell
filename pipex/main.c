/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:26:01 by ilya              #+#    #+#             */
/*   Updated: 2025/08/09 01:11:55 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**init_split_and_clean(char *arg)
{
	char	**buf;
	char	*tmp;
	int		i;

	buf = space_prot_splitter(arg);
	if (!buf)
		return (NULL);
	space_unreplacer(&buf);
	i = -1;
	while (buf[++i])
	{
		if (i == 0 && access(buf[i], X_OK) == 0)
			continue ;
		tmp = quot_escape_remover(buf[i]);
		free(buf[i]);
		buf[i] = tmp;
		tmp = NULL;
	}
	return (buf);
}

static void	init_commands(t_pipex *pipex, char **envp)
{
	pipex->cmd1_path = cmd_validator(pipex->cmd1_args[0], envp);
	pipex->cmd2_path = cmd_validator(pipex->cmd2_args[0], envp);
}

static int	initializer(char **argv, t_pipex *pipex, char **envp)
{
	if (!init_fds(argv, pipex))
		return (0);
	pipex->cmd1_args = init_split_and_clean(argv[2]);
	pipex->cmd2_args = init_split_and_clean(argv[3]);
	if (!pipex->cmd1_args || !pipex->cmd2_args)
		return (perror("./pipex: malloc"), 0);
	if (pipex->cmd1_args && pipex->cmd1_args[0])
		pipex->cmd1 = ft_strdup(pipex->cmd1_args[0]);
	if (pipex->cmd2_args && pipex->cmd2_args[0])
		pipex->cmd2 = ft_strdup(pipex->cmd2_args[0]);
	init_commands(pipex, envp);
	if (pipex->cmd1_args[0] && !pipex->cmd1_path)
		pipex->cmd1_path = ft_strdup(pipex->cmd1_args[0]);
	if (pipex->cmd2_args[0] && !pipex->cmd2_path)
		pipex->cmd2_path = ft_strdup(pipex->cmd2_args[0]);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		pipex;
	t_chld		ctx;
	int			exit_code;

	if (argc != 5)
		return (arg_error_printer(), 1);
	pipex = (t_pipex){0};
	ctx = (t_chld){0};
	empty_handler(argv, &pipex);
	if (!initializer(argv, &pipex, envp))
		return (pipex_cleaner(&pipex), 127);
	exit_code = exec(&pipex, &ctx, envp);
	pipex_cleaner(&pipex);
	return (exit_code);
}
