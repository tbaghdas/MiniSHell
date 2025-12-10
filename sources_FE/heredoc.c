/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:54:05 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/11 03:26:17 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_waiter(t_shell *sh)
{
	int		status;
	int		last_status;

	last_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
		sh->exit_code = last_status;
	}
}

static void	heredoc_read_child(int wfd, t_redir *rd, t_shell *sh)
{
	char	*line;

	while (42)
	{
		line = readline(">");
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
	close(wfd);
	safe_free(line);
	free_front_end_shell(sh);
	free_env(sh);
	exit(0);
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
	{
		signal(SIGINT, SIG_DFL);
		heredoc_read_child(wfd, rd, sh);
	}
	signal_waiter(sh);
	signal(SIGINT, sigint_handler);
	return (wfd);
}

static int	heredoc_writer(t_redir *rd, t_shell *sh)
{
	int		wfd;
	int		rfd;

	wfd = temp_file_writer(rd, sh);
	rfd = open(".tmp", O_RDONLY, 0600);
	if (rfd == -1)
		fatal_error("open", sh);
	if (close(wfd) == -1)
		fatal_error("close", sh);
	wfd = -1;
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
				rd->fd = heredoc_writer(rd, sh);
			rd = rd->next;
		}
		cmd_cur = cmd_cur->next;
	}
	return (0);
}
