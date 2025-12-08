/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:54:05 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/09 01:40:07 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	temp_file_writer(t_redir *rd, t_shell *sh)
{
	int		wfd;
	char	*line;

	wfd = open(".tmp", O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (wfd == -1)
		fatal_error("open", sh);
	while (42)
	{
		line = readline(">");
		if (!line || !ft_strcmp(rd->target, line))
		{
			free(line);
			break ;
		}
		if (ft_strchr(line, '$') && rd->do_expand)
			heredoc_expander(&line, sh);
		if (write(wfd, line, ft_strlen(line)) == -1)
			fatal_error("write (2)", sh);
		if (write(wfd, "\n", 1) == -1)
			fatal_error("write (2)", sh);
		free(line);
	}
	return (wfd);
}

static int	heredoc_writer(t_redir *rd, t_shell *sh)
{
	int		wfd;
	int		rfd;

	wfd = temp_file_writer(rd, sh);
	if (close(wfd) == -1)
		fatal_error("close", sh);
	wfd = -1;
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
				rd->fd = heredoc_writer(rd, sh);
			rd = rd->next;
		}
		cmd_cur = cmd_cur->next;
	}
	return (0);
}
