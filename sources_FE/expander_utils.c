/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 01:16:48 by ikiriush          #+#    #+#             */
/*   Updated: 2025/12/10 04:24:49 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_coder(char **src, char **dst, t_shell *sh)
{
	char	*code;
	char	*pcode;

	if ((*src)[1] != '?')
		return (0);
	code = ft_itoa(sh->exit_code);
	if (!code)
		fatal_error("malloc", sh);
	pcode = code;
	while (*pcode)
		*(*dst)++ = *pcode++;
	free(code);
	*src += 2;
	return (1);
}

int	quote_changes(char c, t_qstate qs)
{
	if ((c == '\'' && (qs == SINGLE || qs == NONE))
		|| (c == '\"' && (qs == DOUBLE || qs == NONE)))
		return (1);
	return (0);
}

int	expand_needed(char *s, t_qstate qs, t_toktyp type)
{
	if (*s == '$' && qs != SINGLE && type != HEREDOC
		&& (s[1] && (legit(s[1]) || s[1] == '?')))
		return (1);
	return (0);
}

void	handle_redirs(t_shell *sh)
{
	t_redir	*rd;
	t_cmd	*cmd;

	cmd = sh->cmd;
	while (cmd)
	{
		rd = cmd->redirs;
		while (rd)
		{
			if (ft_strchr(rd->target, '\'') || ft_strchr(rd->target, '\"')
				|| ft_strchr(rd->target, '$'))
				actual_expander(&rd->target, sh, rd->type);
			rd = rd->next;
		}
		cmd = cmd->next;
	}
}

void	handle_cmds(t_shell *sh)
{
	int		i;
	t_cmd	*cmd;

	cmd = sh->cmd;
	while (cmd)
	{
		i = 0;
		while (cmd->argv[i])
		{
			if (ft_strchr(cmd->argv[i], '\'') || ft_strchr(cmd->argv[i], '\"')
				|| ft_strchr(cmd->argv[i], '$'))
				actual_expander(&cmd->argv[i], sh, WORD);
			i++;
		}
		cmd = cmd->next;
	}
}
