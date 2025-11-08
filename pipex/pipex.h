/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:19:56 by ilya              #+#    #+#             */
/*   Updated: 2025/08/09 01:22:35 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		empty1;
	char	*cmd1;
	char	*cmd1_path;
	char	**cmd1_args;
	char	*cmd2;
	char	*cmd2_path;
	char	**cmd2_args;
}	t_pipex;

typedef struct s_chld
{
	pid_t	pid1;
	pid_t	pid2;
	int		exit_code;
	int		pipefd[2];
}	t_chld;

typedef struct s_space_ctx
{
	int		i;
	int		in_sq;
	int		in_dq;
	int		first_space_protected;
	int		is_path;
}	t_space_ctx;

typedef struct s_qe_ctx
{
	int		i;
	int		j;
	int		in_single;
	int		in_double;
}	t_qe_ctx;

void	arg_error_printer(void);
void	close_io_fds(t_pipex *pipex);
void	cmd_error_printer(char *str);
char	*cmd_validator(char *arg, char **envp);
void	empty_handler(char **argv, t_pipex *pipex);
int		exec(t_pipex *pipex, t_chld *ctx, char **envp);
void	exec_checker(char *path, t_pipex *pipex, t_chld *ctx, int no);
void	fd_closer(t_pipex *pipex);
void	freer(char ***arr);
int		init_fds(char **argv, t_pipex *pipex);
int		is_direct_path(const char *arg);
void	piper_cmd1(t_pipex *pipex, t_chld *ctx, char **envp);
void	piper_cmd2(t_pipex *pipex, t_chld *ctx, char **envp);
void	pipex_cleaner(t_pipex *pipex);
char	*quot_escape_remover(char *arg);
char	**space_prot_splitter(char *arg);
void	space_unreplacer(char ***argv);
#endif