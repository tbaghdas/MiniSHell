/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 23:35:23 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/17 05:07:43 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_tokens(t_shell *sh)
{
	t_token	*tmp;

	if (!sh)
		return ;
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

	if (!sh || !sh->cmd)
		return ;
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

	if (!sh || !sh->cmd)
		return ;
	i = 0;
	if (sh->cmd->argv)
	{
		while (sh->cmd->argv[i])
			free(sh->cmd->argv[i++]);
		free(sh->cmd->argv);
		sh->cmd->argv = NULL;
	}
	if (sh->cmd->redirs)
		free_redirs(sh);
}

void	free_fe_shell(t_shell *sh)
{
	t_cmd	*tmp;

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
	sh->tok = NULL;
	sh->cmd = NULL;
}
