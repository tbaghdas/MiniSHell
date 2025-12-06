/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 01:16:48 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/07 00:46:43 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*actual_expander(char *line, t_shell *sh)
{
	int			i;
	int			j;
	char		*buf;
	t_qstate	qs;

	i = 0;
	j = 0;
	qs = NONE;
	buf = malloc(VAR_NAME_MAX * sizeof(char));
	if (!buf)
		fatal_error("malloc", sh);
	while (line[i])
	{
		if ((line[i] == '\'' && (qs == NONE || qs == SINGLE))
			|| (line[i] == '\"' && (qs == NONE || qs == DOUBLE)))
			qstate_updater(line[i++], &qs);
		else if (line[i] == '$' && qs != SINGLE)
		{
			if (env_extractor(line, buf, &i, &j))
				fatal_error("malloc", sh);
		}
		else
			buf[j++] = line[i++];
	}
	return (buf[j] = '\0', buf);
}

static void	handle_redirs(t_shell *sh)
{
	t_redir	*rd;
	t_cmd	*cmd;
	char	*buf;

	if (sh->cmd)
		rd = sh->cmd->redirs;
	cmd = sh->cmd;
	while (cmd)
	{
		while (rd)
		{
			if (ft_strchr(rd->target, '\'') || ft_strchr(rd->target, '\"')
				|| ft_strchr(rd->target, '$'))
			{
				buf = ft_strdup(rd->target);
				if (!buf)
					fatal_error("malloc", sh);
				free(rd->target);
				rd->target = actual_expander(buf, sh);
				free(buf);
			}
			rd = rd->next;
		}
		cmd = cmd->next;
	}
}

static void	handle_cmds(t_shell *sh)
{
	int		i;
	char	*buf;
	t_cmd	*cmd;

	cmd = sh->cmd;
	while (cmd)
	{
		i = 0;
		while (cmd->argv[i])
		{
			if (ft_strchr(cmd->argv[i], '\'') || ft_strchr(cmd->argv[i], '\"')
				|| ft_strchr(cmd->argv[i], '$'))
			{
				buf = ft_strdup(cmd->argv[i]);
				if (!buf)
					fatal_error("malloc", sh);
				free(cmd->argv[i]);
				cmd->argv[i] = actual_expander(buf, sh);
				free(buf);
			}
			i++;
		}
		cmd = cmd->next;
	}
}

void	expander(t_shell *sh)
{
	handle_cmds(sh);
	handle_redirs(sh);
}
