/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:44:23 by ikiriush          #+#    #+#             */
/*   Updated: 2025/11/12 23:58:31 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/libft.h"
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

typedef struct s_shell
{
	char *cmd;
	char *args;
} t_shell;

typedef enum s_toktyp
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APP,
	HEREDOC	
} t_toktyp;

typedef struct s_token
{
	t_toktyp	type;
	char		*value;
	t_token		*next;
}	t_token;
