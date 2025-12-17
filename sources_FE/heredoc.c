/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:54:05 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/17 05:27:32 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc_cleanup(int wfd, char *line, t_shell *sh)
{
	if (wfd >= 0)
	{
		close(wfd);
		wfd = -1;
	}
	safe_free(line);
	free_fe_shell(sh);
	free_env(sh);
}

static void	heredoc_read_child(int wfd, t_redir *rd, t_shell *sh)
{
	char	*line;

	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		line = readline(">");
		if (g_signum == SIGINT)
			exit ((heredoc_cleanup(wfd, line, sh), 130));
		if (!line)
		{
			syntax_errorer_heredoc(rd, sh);
			break ;
		}
		else if (!ft_strcmp(rd->target, line))
			break ;
		if (ft_strchr(line, '$') && rd->do_expand)
			heredoc_expander(&line, sh);
		if (write(wfd, line, ft_strlen(line)) == -1)
			fatal_error("write (2)", sh);
		if (write(wfd, "\n", 1) == -1)
			fatal_error("write (2)", sh);
		free(line);
	}
	exit((heredoc_cleanup(wfd, line, sh), 0));
}

static int	temp_file_writer(t_redir *rd, t_shell *sh)
{
	int		wfd;
	pid_t	pid;

	wfd = open(".tmp", O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (wfd == -1)
		fatal_error("open", sh);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		fatal_error("fork", sh);
	if (pid == 0)
		heredoc_read_child(wfd, rd, sh);
	close(wfd);
	wfd = -1;
	if (wait_heredoc_child(pid, sh) == -1)
		perror("waitpid");
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (sh->exit_code == 130)
		return (-1);
	return (0);
}

static int	heredoc_writer(t_redir *rd, t_shell *sh)
{
	int	rfd;

	if (temp_file_writer(rd, sh) == -1)
	{
		unlink(".tmp");
		return (-1);
	}
	rfd = open(".tmp", O_RDONLY, 0600);
	if (rfd == -1)
		fatal_error("open", sh);
	unlink(".tmp");
	return (rfd);
}

int	process_heredoc(t_shell *sh)
{
	t_cmd	*cmd_cur;
	t_redir	*rd;

	cmd_cur = sh->cmd;
	while (cmd_cur)
	{
		rd = cmd_cur->redirs;
		while (rd)
		{
			if (rd->type == HEREDOC)
			{
				rd->fd = heredoc_writer(rd, sh);
				if (rd->fd == -1)
					return (-1);
			}
			rd = rd->next;
		}
		cmd_cur = cmd_cur->next;
	}
	return (0);
}
