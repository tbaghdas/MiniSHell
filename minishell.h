/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:44:23 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/29 19:45:14 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft/libft.h"
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

# include "front_end.h"
# include "built_in/built_in.h"
# include "signals/signals.h"

typedef struct s_shell
{
	char	*cmd;
	char	*args;
	int		exit_code;
} t_shell;

typedef struct s_env
{
	char	*key;
	char	*value;
	bool	export_flag;
	struct s_env *next;
} t_env;

void	main_loop(t_shell *sh, char **envp);
int		parse_input(t_shell **sh, char **envp, char *line);

#endif
