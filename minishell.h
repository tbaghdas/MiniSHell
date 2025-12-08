/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:44:23 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/08 14:28:29 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>

# include "libft/libft.h"
# include "sources_FE/front_end.h"
# include "built_in/built_in.h"
# include "signals/signals.h"
# include "cmd_parsing/cmd_parser.h"
// # include "gnl/get_next_line.h"

extern volatile sig_atomic_t	g_signum;

typedef struct s_shell
{
	t_cmd	*cmd;
	t_env	*env;
	t_token	*tok;
	int		exit_code;
}	t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			export_flag;
	struct s_env	*next;
}	t_env;

void	free_front_end_shell(t_shell *sh);
void	main_loop(t_shell *sh, char **envp);
int		parse_input(t_shell *sh, char **envp, char *line);
void	print_cmds(t_shell *sh);

#endif
