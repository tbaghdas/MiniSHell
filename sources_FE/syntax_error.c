/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:44:44 by ilya              #+#    #+#             */
/*   Updated: 2025/12/06 19:08:31 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_errorer(char *line, t_shell *sh)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("'\n", 2);
	free_front_end_shell(sh);
	sh->exit_code = 2; //TODO?
}

void	fatal_error(char *line, t_shell *sh)
{
	int	saved;

	saved = errno;
	free_front_end_shell(sh);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(saved), 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

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
	free_tokens(sh);
	while (sh->cmd)
	{
		tmp = sh->cmd->next;
		free_cmd(sh);
		free(sh->cmd);
		sh->cmd = tmp;
	}
}
