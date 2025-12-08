/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 23:35:23 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/09 01:39:44 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_tokens(t_shell *sh)
{
	t_token	*tmp;

	while (sh->tok)
	{
		tmp = sh->tok->next;
		if (sh->tok->content)
			free(sh->tok->content);
		free(sh->tok);
		sh->tok = tmp;
	}
}

static void	free_redirs(t_shell *sh)
{
	t_redir	*tmp;

	while (sh->cmd->redirs)
	{
		tmp = sh->cmd->redirs->next;
		if (sh->cmd->redirs->target)
			free(sh->cmd->redirs->target);
		if (sh->cmd->redirs->fd >= 0)
		{
			if (close(sh->cmd->redirs->fd) == -1)
				perror("close");
			sh->cmd->redirs->fd = -1;
		}
		free(sh->cmd->redirs);
		sh->cmd->redirs = tmp;
	}
}

static void	free_cmd(t_shell *sh)
{
	int		i;

	i = 0;
	while (sh->cmd->argv[i])
		free(sh->cmd->argv[i++]);
	free(sh->cmd->argv);
	if (sh->cmd->redirs)
		free_redirs(sh);
}

void	free_front_end_shell(t_shell *sh)
{
	int		i;
	int		j;
	t_cmd	*tmp;

	i = 0;
	j = 0;
	if (!sh)
		return ;
	free_tokens(sh);
	while (sh->cmd)
	{
		tmp = sh->cmd->next;
		free_cmd(sh);
		free(sh->cmd);
		sh->cmd = tmp;
	}
}
