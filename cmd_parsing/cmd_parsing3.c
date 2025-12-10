/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaghdas <tbaghdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:10:55 by tbaghdas          #+#    #+#             */
/*   Updated: 2025/12/11 03:13:45 by tbaghdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(int in_fd, int out_fd)
{
	if (in_fd != -1)
		close(in_fd);
	if (out_fd != -1)
		close(out_fd);
}

int	iterate_redirs_and_open(t_redir *r, int *in_fd, int *out_fd)
{
	int	new_fd;

	while (r != NULL)
	{
		new_fd = handle_open_redir(r);
		if (new_fd == -1)
			return (close_fds(*in_fd, *out_fd), -1);
		if (r->type == REDIR_IN || r->type == HEREDOC)
		{
			if (*in_fd != -1)
				close(*in_fd);
			*in_fd = new_fd;
		}
		else if (r->type == REDIR_OUT || r->type == REDIR_APP)
		{
			if (*out_fd != -1)
				close(*out_fd);
			*out_fd = new_fd;
		}
		r = r->next;
	}
	return (0);
}

int	apply_final_dups(int in_fd, int out_fd)
{
	int	ret_val;

	ret_val = 0;
	if (in_fd != -1)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
			ret_val = -1;
	}
	if (out_fd != -1)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1 && ret_val == 0)
			ret_val = -1;
		close(out_fd);
	}
	return (ret_val);
}

int	apply_redirs(t_cmd *cmd)
{
	int	in_fd;
	int	out_fd;

	if (cmd == NULL)
		return (-1);
	in_fd = -1;
	out_fd = -1;
	if (iterate_redirs_and_open(cmd->redirs, &in_fd, &out_fd) == -1)
	{
		return (-1);
	}
	if (apply_final_dups(in_fd, out_fd) == -1)
	{
		return (-1);
	}
	return (0);
}

void	free_split(char **paths)
{
	int	i;

	if (paths == NULL)
		return ;
	i = 0;
	while (paths[i] != NULL)
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}
